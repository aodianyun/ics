#ifndef __ADCLOUD_APP_HPP__
#define __ADCLOUD_APP_HPP__
#include <string>
#include <vector>

namespace adcloud{
namespace app{


typedef unsigned int ClientId;
class IAppListener{
public:
	virtual ~IAppListener(){};
	virtual void L_ClientIn(const ClientId& id,const std::string& addr,const std::string&plat,void*param,int size) = 0;
	virtual void L_ClientOut(const ClientId& id) = 0;
	virtual void L_ClientData(const ClientId& id,void* buf,int size) = 0;
	virtual void L_AppData(const std::string& appid,void*buf,int size) = 0;
	virtual void L_AppEnter(const std::string& appid) = 0;
	virtual void L_AppLeave(const std::string& appid) = 0;
	virtual void L_Close() = 0;
};
class IApp{
public:
	virtual ~IApp(){};
	virtual void Stop() = 0;
	virtual void Release()=0;
	virtual bool SendToClient(const ClientId& id,void* buf,int size) = 0;
	virtual bool CloseClient(const ClientId& id) = 0;
	virtual bool AddScope(const std::string& scope,const ClientId& id) = 0;
	virtual bool DelScope(const std::string& scope,const ClientId& id) = 0;
	virtual bool SendToScope(const std::string& scope,void* buf,int size) = 0;
	virtual bool Broadcast(void*buf,int size) = 0;
	virtual bool SendToApp(const std::string& appid,void*buf,int size)=0;
	virtual bool FollowOtherApp(const std::string& appid) = 0;
	virtual bool UnFollowOtherApp(const std::string& appid) = 0;
};
extern "C" IApp* Start(const std::string& appid,const std::string& password, const std::vector<std::string>& proxy_addrs,IAppListener* lis,int* error ); // ip:port


}
}

#endif
