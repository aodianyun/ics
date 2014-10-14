#include <tchar.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include "../include/adcloud_client.hpp"
#include "./json/json/value.h"
#include "code.hpp"

struct SendPkt{
	int cmd;
	char nick[20];
	char passwd[10];
	char text[1024];
};

struct RcvPket{
	int srv; //100:linux
	int cmd; //8:REG, 88:LOGIN,888:chatText;
	char rs[20];
	char text[1024];
};

class ClientListener:public adcloud::IListener{
public:
	virtual ~ClientListener(){}
	virtual void L_OnOpenFail(){
		std::cout << "连接通讯库失败,请确认appid正确，且对应的服务端已经正确启动！" << std::endl;
	}
	virtual void L_OnMessage(adcloud::ConnectionRef* cli,void* data,int size){
		RcvPket* pRcv= (RcvPket*)data;
		if(pRcv->srv == 100){
			DoLinuxThing(cli,pRcv);
		}else{
			Code code;
			Json::Value* val = code.Decode(data,size);
			Json::Value& ms = *val;
			DoSomeThing(cli,ms);
			delete val;
		}
	}
	virtual void L_OnOpen(adcloud::ConnectionRef* cli){
		std::cout << "连接通讯库成功" << std::endl;
	}
	virtual void L_OnClose(adcloud::ConnectionRef* cli){
		std::cout << "接收到服务器关闭" << std::endl;
	}
	void DoLinuxThing(adcloud::ConnectionRef* cli,RcvPket* pRcv){
	
		if(pRcv->cmd == 0){
			HANDLE hThread = CreateThread(NULL,0,LinuxThread,(void*)cli,0,NULL);
		}else if(pRcv->cmd == 888){
			std::cout<<"收到群聊报文:"<<pRcv->text<<std::endl;
		}else if(pRcv->cmd == 8){
			Sleep(1000);
			if(!strcmp(pRcv->rs,"success")){
				std::cout<<"注册成功！"<<std::endl;
			}else{
				std::cout<<"注册失败！"<<std::endl;
			}
		}else if(pRcv->cmd == 88){
			Sleep(1000);
			if(!strcmp(pRcv->rs,"success")){
				std::cout<<"登录成功！"<<std::endl;
			}else{
				std::cout<<"登录失败！"<<std::endl;
			}
		}
		
	}
	void DoSomeThing(adcloud::ConnectionRef* cli,const Json::Value& ms){
		std::string cmd = ms["cmd"].asString();
		
		if(cmd == "node"){
			HANDLE hThread = CreateThread(NULL,0,NodeThread,(void*)cli,0,NULL);
		}else if(cmd == "chatText"){
			std::string text = ms["text"].asString();
			std::cout<<"收到群聊报文:"<<text<<std::endl;
		}else if(cmd == "REG"){
			Sleep(1000);
			std::string rs = ms["rs"].asString();
			if(rs == "success"){
				std::cout<<"注册成功！"<<std::endl;
			}else{
				std::cout<<"注册失败！"<<std::endl;
			}
		}else if(cmd == "LOGIN"){
			Sleep(1000);
			std::string rs = ms["rs"].asString();
			if(rs == "success"){
				std::cout<<"登录成功！"<<std::endl;
			}else{
				std::cout<<"登录失败！"<<std::endl;
			}
		}
		
	}
protected:
	static  DWORD  WINAPI LinuxThread(void* arg){
		adcloud::ConnectionRef* cli = (adcloud::ConnectionRef*)arg;
		int op = 0;
		std::cout<<"*********LINUX服务器连接成功，请选择相应操作*********"<<std::endl;
		std::cout<<"\n1:********模拟注册********\n2:********模拟登录********\n3:******启动多个客户端模拟群聊******"<<std::endl;
		int trynum = 5;
		while(trynum--){
		std::cin>>op;
		switch(op){
		case 1:{
			std::cout<<"请输入你要注册的用户名和密码"<<std::endl;
			SendPkt spt;
			spt.cmd = 8;
			std::cin>>spt.nick>>spt.passwd;
			std::cout<<spt.nick<<spt.passwd;
			if(cli->Send((void*)&spt,sizeof(spt))){
				std::cout<<"注册信息发送成功,可以查看服务器的DEMO的处理"<<std::endl;
			}
			   }
			   break;
		case 2:{
			std::cout<<"请输入你要登录的用户名和密码"<<std::endl;
			SendPkt spt;
			spt.cmd = 88;
			std::cin>>spt.nick>>spt.passwd;
			if(cli->Send((void*)&spt,sizeof(spt))){
				std::cout<<"登录信息发送成功,可以查看服务器的DEMO的处理"<<std::endl;
			}
			   }
			   break;
		case 3:{
			std::cout<<"请输入聊天信息"<<std::endl;
			SendPkt spt;
			spt.cmd = 888;
			std::cin>>spt.text;
			std::cout<<spt.text;
			if(cli->Send((void*)&spt,sizeof(spt))){
				std::cout<<"群聊信息发送成功,可以查看服务器的DEMO的处理"<<std::endl;
			}
			   }
			   break;
		}
		}
		return 0;
	}
	static  DWORD  WINAPI NodeThread(void* arg){
		adcloud::ConnectionRef* cli = (adcloud::ConnectionRef*)arg;
		int op = 0;
		std::cout<<"*********服务器连接成功，请选择相应操作*********"<<std::endl;
		std::cout<<"\n1:********模拟注册********\n2:********模拟登录********\n3:******启动多个客户端模拟群聊******"<<std::endl;
		int trynum = 5;
		while(trynum--){
		std::cin>>op;
		switch(op){
		case 1:{
			std::cout<<"请输入你要注册的用户名和密码"<<std::endl;
			std::string nick,passwd;
			std::cin>>nick>>passwd;
			Json::Value val;
			val["cmd"] = "REG";
			val["nick"] = nick;
			val["passwd"] = passwd;
			Code code;
			std::string outmsg;
			code.Encode(val,&outmsg);
			if(cli->Send((void*)outmsg.c_str(),(int)outmsg.size())){
				std::cout<<"注册信息发送成功,可以查看服务器的DEMO的处理"<<std::endl;
			}
			   }
			   break;
		case 2:{
			std::cout<<"请输入你要登录的用户名和密码"<<std::endl;
			std::string nick,passwd;
			std::cin>>nick>>passwd;
			Json::Value val;
			val["cmd"] = "LOGIN";
			val["nick"] = nick;
			val["passwd"] = passwd;
			Code code;
			std::string outmsg;
			code.Encode(val,&outmsg);
			if(cli->Send((void*)outmsg.c_str(),(int)outmsg.size())){
				std::cout<<"登录信息发送成功,可以查看服务器的DEMO的处理"<<std::endl;
			}
			   }
			   break;
		case 3:{
			std::cout<<"请输入聊天信息"<<std::endl;
			std::string text;
			std::cin>>text;
			Json::Value val;
			val["cmd"] = "chatText";
			val["text"] = text;
			Code code;
			std::string outmsg;
			code.Encode(val,&outmsg);
			if(cli->Send((void*)outmsg.c_str(),(int)outmsg.size())){
				std::cout<<"群聊信息发送成功,可以查看服务器的DEMO的处理"<<std::endl;
			}
			   }
			   break;
		}
		}
		return 0;
	}
};

bool GetAppid(std::string* pAppid){
	std::ifstream in("../../config.txt");
	if(!in)
	{
		std::cerr << "打开配置文件失败\n";
		return false;
	}
	std::string str;
	while(getline(in, str))
	{
		std::string::size_type index = str.find("Appid:",0);
		if(index != std::string::npos){
			index += sizeof("Appid:");
			*pAppid = str.substr(index-1);
			return true;
		}
	}

	return false;
}


int main(int argc, _TCHAR* argv[])
{
	std::vector<std::string> addrs;
	addrs.push_back("service.ics.aodianyun.com:8365");
	ClientListener lis;
	std::string s;
	std::string Appid;
	GetAppid(&Appid);
	if(Appid.empty()||Appid == "demo"){
		std::cout<<"请修改config的应用编号Appid后重新启动"<<std::endl;
		return 0;
	}
	adcloud::Open(&s,addrs,Appid,&lis);//这里的APPID:"app1"修改成自己的APPID;
	while(true){
		Sleep(1000);
	}
	return 0;
}