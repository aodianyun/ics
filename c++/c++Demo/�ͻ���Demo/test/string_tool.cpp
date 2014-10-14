

#include ".\string_tool.h"

#include <Windows.h>

using namespace std;
StringTool::StringTool(void)
{
}

StringTool::~StringTool(void)
{
}

std::string StringTool::ws2s(const std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
	setlocale(LC_ALL, "chs"); 
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest,0,_Dsize);
	wcstombs(_Dest,_Source,_Dsize);
	std::string result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}
std::wstring StringTool::s2ws(const std::string& s)
{
	std::string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
	setlocale(LC_ALL, "chs"); 
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	std::wstring result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}
bool StringTool::UTF82Unicode(const char *input_utf8,std::wstring & outdata)
{
	if (input_utf8 == NULL) 
	{  // input wrong.
		return false;
	}

	const char* p_current_char = input_utf8;
	unsigned long unicode_length = 0;
	char current_char;
	// calculate the size to locate
	do {
		// get the begining char
		current_char = *p_current_char;

		if ((current_char  & 0x80) == 0) {
			// 0xxxxxxx
			p_current_char++;
		} else if ((current_char  & 0xe0) == 0xc0) {
			// < 110x-xxxx 10xx-xxxx
			p_current_char += 2;
		} else if ((current_char  & 0xf0) == 0xe0) {
			// < 1110-xxxx 10xx-xxxx 10xx-xxxx
			p_current_char += 3;
		} else if ((current_char  & 0xf8) == 0xf0) {
			// < 1111-0xxx 10xx-xxxx 10xx-xxxx 10xx-xxxx
			p_current_char += 4;

		} else if ((current_char & 0xfc) == 0xf8) {
			// 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
			p_current_char += 5;
		} else {
			// if((current_char & 0xfe) == 0xfc)
			// 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
			p_current_char += 6;
		}
		unicode_length++;
	}
	while (current_char != 0);

	//outdata = std::wstring(unicode_length);
	outdata.resize(unicode_length);
	unsigned long unicode_index = 0;
	p_current_char = input_utf8;

	do {
		current_char = *p_current_char;

		if ((current_char & 0x80) == 0) {
			outdata[unicode_index] = p_current_char[0];

			p_current_char++;
		} else if ((current_char & 0xE0) == 0xC0) {
			// < 110x-xxxx 10xx-xxxx
			wchar_t &wide_char = outdata[unicode_index];
			wide_char  = (p_current_char[0] & 0x3F) << 6;
			wide_char |= (p_current_char[1] & 0x3F);

			p_current_char += 2;
		} else if ((current_char & 0xF0) == 0xE0) {
			// < 1110-xxxx 10xx-xxxx 10xx-xxxx
			wchar_t &wide_char = outdata[unicode_index];

			wide_char  = (p_current_char[0] & 0x1F) << 12;
			wide_char |= (p_current_char[1] & 0x3F) << 6;
			wide_char |= (p_current_char[2] & 0x3F);

			p_current_char += 3;
		} else if ((current_char & 0xF8) == 0xF0) {
			// < 1111-0xxx 10xx-xxxx 10xx-xxxx 10xx-xxxx
			wchar_t &wide_char = outdata[unicode_index];

			wide_char  = (p_current_char[0] & 0x0F) << 18;
			wide_char |= (p_current_char[1] & 0x3F) << 12;
			wide_char |= (p_current_char[2] & 0x3F) << 6;
			wide_char |= (p_current_char[3] & 0x3F);

			p_current_char += 4;
		} else if ((current_char & 0xfc) == 0xf8) {
			// 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
			wchar_t &wide_char = outdata[unicode_index];

			wide_char = (p_current_char[0] & 0x07) << 24;
			wide_char |= (p_current_char[1] & 0x3F) << 18;
			wide_char |= (p_current_char[2] & 0x3F) << 12;
			wide_char |= (p_current_char[3] & 0x3F) << 6;
			wide_char |= (p_current_char[4] & 0x3F);

			p_current_char += 5;
		} else {
			// if((*current_char & 0xfe) == 0xfc)
			// 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx

			wchar_t &wide_char = outdata[unicode_index];

			wide_char = (p_current_char[0] & 0x03) << 30;
			wide_char |= (p_current_char[1] & 0x3F) << 24;
			wide_char |= (p_current_char[2] & 0x3F) << 18;
			wide_char |= (p_current_char[3] & 0x3F) << 12;
			wide_char |= (p_current_char[4] & 0x3F) << 6;
			wide_char |= (p_current_char[5] & 0x3F);
			p_current_char += 6;
		}
		unicode_index++;
	} while (current_char != 0);

	return true;
}

void StringTool::UTF_8ToUnicode(wchar_t* pOut,char *pText)
{
	char* uchar = (char *)pOut;

	uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
	uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);

	return;
}

void StringTool::UnicodeToUTF_8(char* pOut,wchar_t* pText)
{
	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后
	char* pchar = (char *)pText;

	pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
	pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
	pOut[2] = (0x80 | (pchar[0] & 0x3F));

	return;
}

void StringTool::UnicodeToGB2312(char* pOut,wchar_t uData)
{
	WideCharToMultiByte(CP_ACP,NULL,&uData,1,pOut,sizeof(wchar_t),NULL,NULL);
	return;
}     

void StringTool::Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer)
{
	::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
	return ;
}

void StringTool::GB2312ToUTF_8(string& pOut,char *pText, int pLen)
{
	char buf[4];
	int nLength = pLen* 3;
	char* rst = new char[nLength];

	memset(buf,0,4);
	memset(rst,0,nLength);

	int i = 0;
	int j = 0;      
	while(i < pLen)
	{
		//如果是英文直接复制就可以
		if( *(pText + i) >= 0)
		{
			rst[j++] = pText[i++];
		}
		else
		{
			wchar_t pbuffer;
			Gb2312ToUnicode(&pbuffer,pText+i);

			UnicodeToUTF_8(buf,&pbuffer);

			unsigned short int tmp = 0;
			tmp = rst[j] = buf[0];
			tmp = rst[j+1] = buf[1];
			tmp = rst[j+2] = buf[2];    

			j += 3;
			i += 2;
		}
	}
	rst[j] = '\0';

	//返回结果
	pOut = rst;             
	delete []rst;   

	return;
}

void StringTool::UTF_8ToGB2312(string &pOut, char *pText, int pLen)
{
	char * newBuf = new char[pLen];
	char Ctemp[4];
	memset(Ctemp,0,4);

	int i =0;
	int j = 0;

	while(i < pLen)
	{
		if(pText[i] > 0)
		{
			newBuf[j++] = pText[i++];                       
		}
		else                 
		{
			WCHAR Wtemp;
			UTF_8ToUnicode(&Wtemp,pText + i);

			UnicodeToGB2312(Ctemp,Wtemp);

			newBuf[j] = Ctemp[0];
			newBuf[j + 1] = Ctemp[1];

			i += 3;    
			j += 2;   
		}
	}
	newBuf[j] = '\0';

	pOut = newBuf;
	delete []newBuf;

	return; 
}  

