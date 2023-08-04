#pragma once
class memberFuncHeader
{
public:
	memberFuncHeader() {}
	~memberFuncHeader() {}

public:
	void vOutputValueByPointer(char* p_cStr);
	bool bOutputRet(int p_iValue, int p_iLen);
	int iConstParamFunc(const char* p_cStr, const int p_iValue);
	char* pcOutputValueByReference(const char* p_cStr, int& p_iLen);
	virtual void vOutputValueByPointer_vir(char* p_cStr);
	virtual bool bOutputRet_vir(int p_iValue, int p_iLen);
	virtual int iConstParamFunc_vir(const char* p_cStr, const int p_iValue);
	virtual char* pcOutputValueByReference_vir(const char* p_cStr, int& p_iLen);
};

