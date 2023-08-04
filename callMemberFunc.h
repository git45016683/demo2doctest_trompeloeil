#pragma once

class memberFuncHeader;

class callMemberFunc
{
public:
	callMemberFunc();
	~callMemberFunc();

public:
	int iTest_OutputValueByPointer(char* p_cStr);
	int iTest_bOutputRet(int p_iValue, int p_iLen);
	int iTest_iConstParamFunc(const char* p_cStr, const int p_iValue);
	int iTest_pcOutputValueByReference(const char* p_cStr, int& p_iLen);
	int iTest_vOutputValueByPointer_vir(char* p_cStr);
	int iTest_bOutputRet_vir(int p_iValue, int p_iLen);
private:
	int iTest_iConstParamFunc_vir(const char* p_cStr, const int p_iValue);
	int iTest_pcOutputValueByReference_vir(const char* p_cStr, int& p_iLen);

private:
//public:
	memberFuncHeader* m_pObj;
};

