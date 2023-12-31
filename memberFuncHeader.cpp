#include "memberFuncHeader.h"

void memberFuncHeader::vOutputValueByPointer(char* p_cStr)
{
	p_cStr[0] = 'o';
	p_cStr[1] = 'r';
	p_cStr[2] = 'i';
	p_cStr[3] = 'g';
	p_cStr[4] = 'i';
	p_cStr[5] = 'n';
}

bool memberFuncHeader::bOutputRet(int p_iValue, int p_iLen)
{
	return true;
}

int memberFuncHeader::iConstParamFunc(const char* p_cStr, const int p_iValue)
{
	return 0;
}

char* memberFuncHeader::pcOutputValueByReference(const char* p_cStr, int& p_iLen)
{
	const char* l_pcRet = "null";
	return (char*)l_pcRet;
}

void memberFuncHeader::vOutputValueByPointer_vir(char* p_cStr)
{
}

bool memberFuncHeader::bOutputRet_vir(int p_iValue, int p_iLen)
{
	return false;
}

int memberFuncHeader::iConstParamFunc_vir(const char* p_cStr, const int p_iValue)
{
	return -1;
}

char* memberFuncHeader::pcOutputValueByReference_vir(const char* p_cStr, int& p_iLen)
{
	const char* l_pcRet = "null_vir";
	return (char*)l_pcRet;
}
