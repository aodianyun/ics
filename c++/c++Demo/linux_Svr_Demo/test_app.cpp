#include "app/adcloud_app.hpp"
#include <iostream>
#include <unistd.h>
#include <stdint.h>
#include <cstdlib>

using namespace std;

struct SendPkt{
	int cmd;
	char nick[20];
	char passwd[10];
	char text[1024];
};

struct RcvPket{
	int srv; //100:linux
	int cmd;//8:REG, 88:LOGIN,888:chatText;
	char rs[20];
	char text[1024];
};

uint32_t num_pkt = 0;
uint32_t num_client = 0;
class EchoApp:public adcloud::app::IAppListener{
public:
	EchoApp( const std::string& appid,const std::string& passwd,const std::string& addr)
	:addr_(addr),
	appid_(appid),
	passwd_(passwd),
	scope_("demo"){

	}
	bool start(){
		std::vector<std::string> addrs;
		addrs.push_back(addr_);
		int err;
		app_ = adcloud::app::Start(appid_/*修改成自己的appid*/,passwd_/*修改成自己的密码*/,addrs,this,&err);
		return app_ != NULL;
	}
	virtual ~EchoApp(){

	};
	virtual void L_ClientIn(const adcloud::app::ClientId& id,const std::string& addr){
		
		num_client ++ ;
		this->app_->AddScope(this->scope_,id);
		RcvPket rcv;
		rcv.srv = 100;
		rcv.cmd = 0;
		this->app_->SendToClient(id,(void*)&rcv,sizeof(rcv));
	}
	virtual void L_ClientOut(const adcloud::app::ClientId& id){

		num_client --;
		this->app_->DelScope(this->scope_,id);
	}
	virtual void L_ClientData(const adcloud::app::ClientId& id,void* buf,int size){
		SendPkt* pSpt = (SendPkt*)buf;
		if(sizeof(SendPkt) == size){
			if(pSpt->cmd == 888){//scope
				cout<<"recv scope message:"<<pSpt->text<<endl;
				RcvPket rcv;
				rcv.srv = 100;
				rcv.cmd = 888;
				strcpy(rcv.text,pSpt->text);
				this->app_->SendToScope(this->scope_,(void*)&rcv,sizeof(rcv));
			}else if(pSpt->cmd == 8){//REG
				cout<<"recv Register message:nick:"<<pSpt->nick<<",passwd:"<<pSpt->passwd<<endl;
				RcvPket rcv;
				rcv.srv = 100;
				rcv.cmd = 8;
				strcpy(rcv.rs,"success");
				this->app_->SendToClient(id,(void*)&rcv,sizeof(rcv));
			}else if(pSpt->cmd == 88){//LOGIN
				cout<<"recv login message:nick:"<<pSpt->nick<<",passwd:"<<pSpt->passwd<<endl;
				RcvPket rcv;
				rcv.srv = 100;
				rcv.cmd = 88;
				strcpy(rcv.rs,"success");
				this->app_->SendToClient(id,(void*)&rcv,sizeof(rcv));
			}

		}
	}
	virtual void L_AppData(const std::string& appid,void*buf,int size){
		//cout << "app-data" << appid << " " << std::string((char*)buf,size);
	}
	virtual void L_Close(){
		//cout << "L_Close";
		exit(0);
	}
private:
	std::string addr_;
	std::string passwd_;
	std::string appid_;
	std::string scope_;
	adcloud::app::IApp* app_;
};
int main(int argc,const char* argv[]){
	std::string appid;
	std::string passwd;
	std::string addr = "service.ics.aodianyun.com:8365";
	std::cout<<"Please Input your Appid and Passwd"<<std::endl;
	std::cin>>appid>>passwd;
	if(argc >= 2){
		appid = argv[1];
	}
	if(argc >= 3){
		addr = argv[2];
	}
	EchoApp echo_app(appid,passwd,addr);
	if(echo_app.start()){
		cout << "app.start.success  [" << appid << "  " << addr << "]" << endl;
	}else{
		cout << "app.start.fail  [" << appid << "  " << addr << "]" << endl;
		return -1;
	}
	while(true){
		sleep(1);
		if(num_pkt>0){
			cout << "num_pkt:" << num_pkt << "  num_client:" << num_client;
			num_pkt = 0;
		}
		
	}

}
