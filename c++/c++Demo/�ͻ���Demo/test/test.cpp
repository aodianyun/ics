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
		std::cout << "����ͨѶ��ʧ��,��ȷ��appid��ȷ���Ҷ�Ӧ�ķ�����Ѿ���ȷ������" << std::endl;
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
		std::cout << "����ͨѶ��ɹ�" << std::endl;
	}
	virtual void L_OnClose(adcloud::ConnectionRef* cli){
		std::cout << "���յ��������ر�" << std::endl;
	}
	void DoLinuxThing(adcloud::ConnectionRef* cli,RcvPket* pRcv){
	
		if(pRcv->cmd == 0){
			HANDLE hThread = CreateThread(NULL,0,LinuxThread,(void*)cli,0,NULL);
		}else if(pRcv->cmd == 888){
			std::cout<<"�յ�Ⱥ�ı���:"<<pRcv->text<<std::endl;
		}else if(pRcv->cmd == 8){
			Sleep(1000);
			if(!strcmp(pRcv->rs,"success")){
				std::cout<<"ע��ɹ���"<<std::endl;
			}else{
				std::cout<<"ע��ʧ�ܣ�"<<std::endl;
			}
		}else if(pRcv->cmd == 88){
			Sleep(1000);
			if(!strcmp(pRcv->rs,"success")){
				std::cout<<"��¼�ɹ���"<<std::endl;
			}else{
				std::cout<<"��¼ʧ�ܣ�"<<std::endl;
			}
		}
		
	}
	void DoSomeThing(adcloud::ConnectionRef* cli,const Json::Value& ms){
		std::string cmd = ms["cmd"].asString();
		
		if(cmd == "node"){
			HANDLE hThread = CreateThread(NULL,0,NodeThread,(void*)cli,0,NULL);
		}else if(cmd == "chatText"){
			std::string text = ms["text"].asString();
			std::cout<<"�յ�Ⱥ�ı���:"<<text<<std::endl;
		}else if(cmd == "REG"){
			Sleep(1000);
			std::string rs = ms["rs"].asString();
			if(rs == "success"){
				std::cout<<"ע��ɹ���"<<std::endl;
			}else{
				std::cout<<"ע��ʧ�ܣ�"<<std::endl;
			}
		}else if(cmd == "LOGIN"){
			Sleep(1000);
			std::string rs = ms["rs"].asString();
			if(rs == "success"){
				std::cout<<"��¼�ɹ���"<<std::endl;
			}else{
				std::cout<<"��¼ʧ�ܣ�"<<std::endl;
			}
		}
		
	}
protected:
	static  DWORD  WINAPI LinuxThread(void* arg){
		adcloud::ConnectionRef* cli = (adcloud::ConnectionRef*)arg;
		int op = 0;
		std::cout<<"*********LINUX���������ӳɹ�����ѡ����Ӧ����*********"<<std::endl;
		std::cout<<"\n1:********ģ��ע��********\n2:********ģ���¼********\n3:******��������ͻ���ģ��Ⱥ��******"<<std::endl;
		int trynum = 5;
		while(trynum--){
		std::cin>>op;
		switch(op){
		case 1:{
			std::cout<<"��������Ҫע����û���������"<<std::endl;
			SendPkt spt;
			spt.cmd = 8;
			std::cin>>spt.nick>>spt.passwd;
			std::cout<<spt.nick<<spt.passwd;
			if(cli->Send((void*)&spt,sizeof(spt))){
				std::cout<<"ע����Ϣ���ͳɹ�,���Բ鿴��������DEMO�Ĵ���"<<std::endl;
			}
			   }
			   break;
		case 2:{
			std::cout<<"��������Ҫ��¼���û���������"<<std::endl;
			SendPkt spt;
			spt.cmd = 88;
			std::cin>>spt.nick>>spt.passwd;
			if(cli->Send((void*)&spt,sizeof(spt))){
				std::cout<<"��¼��Ϣ���ͳɹ�,���Բ鿴��������DEMO�Ĵ���"<<std::endl;
			}
			   }
			   break;
		case 3:{
			std::cout<<"������������Ϣ"<<std::endl;
			SendPkt spt;
			spt.cmd = 888;
			std::cin>>spt.text;
			std::cout<<spt.text;
			if(cli->Send((void*)&spt,sizeof(spt))){
				std::cout<<"Ⱥ����Ϣ���ͳɹ�,���Բ鿴��������DEMO�Ĵ���"<<std::endl;
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
		std::cout<<"*********���������ӳɹ�����ѡ����Ӧ����*********"<<std::endl;
		std::cout<<"\n1:********ģ��ע��********\n2:********ģ���¼********\n3:******��������ͻ���ģ��Ⱥ��******"<<std::endl;
		int trynum = 5;
		while(trynum--){
		std::cin>>op;
		switch(op){
		case 1:{
			std::cout<<"��������Ҫע����û���������"<<std::endl;
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
				std::cout<<"ע����Ϣ���ͳɹ�,���Բ鿴��������DEMO�Ĵ���"<<std::endl;
			}
			   }
			   break;
		case 2:{
			std::cout<<"��������Ҫ��¼���û���������"<<std::endl;
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
				std::cout<<"��¼��Ϣ���ͳɹ�,���Բ鿴��������DEMO�Ĵ���"<<std::endl;
			}
			   }
			   break;
		case 3:{
			std::cout<<"������������Ϣ"<<std::endl;
			std::string text;
			std::cin>>text;
			Json::Value val;
			val["cmd"] = "chatText";
			val["text"] = text;
			Code code;
			std::string outmsg;
			code.Encode(val,&outmsg);
			if(cli->Send((void*)outmsg.c_str(),(int)outmsg.size())){
				std::cout<<"Ⱥ����Ϣ���ͳɹ�,���Բ鿴��������DEMO�Ĵ���"<<std::endl;
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
		std::cerr << "�������ļ�ʧ��\n";
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
		std::cout<<"���޸�config��Ӧ�ñ��Appid����������"<<std::endl;
		return 0;
	}
	adcloud::Open(&s,addrs,Appid,&lis);//�����APPID:"app1"�޸ĳ��Լ���APPID;
	while(true){
		Sleep(1000);
	}
	return 0;
}