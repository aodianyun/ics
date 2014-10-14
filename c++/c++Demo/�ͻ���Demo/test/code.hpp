#ifndef _CODE_HPP_
#define _CODE_HPP_
#include "json/json/value.h"
#include "json/json/reader.h"
#include "json/json/writer.h"
#include "string_tool.h"
class Code{
public:
	Json::Value* Decode(void* data, int size);
	bool Encode(const Json::Value& val,std::string* msg);
};

#endif