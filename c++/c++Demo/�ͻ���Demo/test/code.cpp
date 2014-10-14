#include "code.hpp"

Json::Value* Code::Decode(void* data, int size){
	std::string str((char*)data,size);
	std::wstring wdata;
	StringTool::UTF82Unicode(str.c_str(),wdata);
	str = StringTool::ws2s(wdata);
	Json::Value* val = new Json::Value();
	Json::Reader reader;
	reader.parse(str,*val,false);
	return val;
}
bool Code::Encode(const Json::Value& val,std::string* msg){
	Json::StyledWriter writer;
	std::string buf = writer.write(val);
	std::string outmsg;
	StringTool::GB2312ToUTF_8(outmsg,const_cast<char *>(buf.c_str()),(int)buf.size());
	*msg = outmsg;
	return true;
}