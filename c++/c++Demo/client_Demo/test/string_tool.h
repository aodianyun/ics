#pragma once
#include <string>
	class StringTool
	{
	public:
		StringTool(void);
		~StringTool(void);
		static std::string ws2s(const std::wstring& ws);
		static std::wstring s2ws(const std::string& s);
		static bool UTF82Unicode(const char *input_utf8,std::wstring & outdata);

		static void UTF_8ToUnicode(wchar_t* pOut,char *pText);  // 把UTF-8转换成Unicode
		static void UnicodeToUTF_8(char* pOut,wchar_t* pText);  //Unicode 转换成UTF-8
		static void UnicodeToGB2312(char* pOut,wchar_t uData);  // 把Unicode 转换成 GB2312 
		static void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);// GB2312 转换成　Unicode
		static void GB2312ToUTF_8(std::string& pOut,char *pText, int pLen);//GB2312 转为 UTF-8
		static void UTF_8ToGB2312(std::string &pOut, char *pText, int pLen);//UTF-8 转为 GB2312
	};