#ifndef __ADCOUD_CLIENT_HPP__
#define __ADCOUD_CLIENT_HPP__

#include <string>
#include <vector>

#ifdef ADCLOUD_SDK_CPP_EXPORTS
#define ADCLOUD_SDK_API __declspec(dllexport)
#else
#define ADCLOUD_SDK_API __declspec(dllimport)
#endif

namespace adcloud{
	class ConnectionRef{
	public:
		virtual ~ConnectionRef(){}
		virtual bool Send(void* buf,int size)=0;
		virtual void Close()=0;
		virtual void Release() = 0;
	};
	class IListener{
	public:
		virtual ~IListener(){}
		virtual void L_OnOpenFail()=0;
		virtual void L_OnOpen(ConnectionRef* cli) = 0;
		virtual void L_OnMessage(ConnectionRef* cli,void* buf,int size) = 0;
		virtual void L_OnClose(ConnectionRef* cli) = 0;
	};
	//extern ADCLOUD_SDK_API void Open(const std::vector<std::string>& addrs,const std::string& appid,IListener* lis);
	extern "C" ADCLOUD_SDK_API  bool Open(std::string* s, const std::vector<std::string>& addrs,const std::string& appid,IListener* lis);
}
#endif