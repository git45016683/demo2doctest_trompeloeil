#include "callMemberFunc.h"
#include "memberFuncHeader.h"

callMemberFunc::callMemberFunc(memberFuncHeader* p_pObj):m_pObj(nullptr)
{
	m_pObj = p_pObj;
}

callMemberFunc::~callMemberFunc()
{
	if (m_pObj != nullptr)
	{
		delete m_pObj;
		m_pObj = nullptr;
	}
}

int callMemberFunc::iTest_OutputValueByPointer(char* p_cStr)
{
	m_pObj->vOutputValueByPointer(p_cStr);
	return 0;
}

int callMemberFunc::iTest_bOutputRet(int p_iValue, int p_iLen)
{
	return m_pObj->bOutputRet(p_iValue, p_iLen);
}

int callMemberFunc::iTest_iConstParamFunc(const char* p_cStr, const int p_iValue)
{
	return m_pObj->iConstParamFunc(p_cStr, p_iValue);
}

int callMemberFunc::iTest_pcOutputValueByReference(const char* p_cStr, int& p_iLen)
{
	m_pObj->pcOutputValueByReference(p_cStr, p_iLen);
	return 0;
}

int callMemberFunc::iTest_vOutputValueByPointer_vir(char* p_cStr)
{
	m_pObj->vOutputValueByPointer_vir(p_cStr);
	return 0;
}

int callMemberFunc::iTest_bOutputRet_vir(int p_iValue, int p_iLen)
{
	return m_pObj->bOutputRet_vir(p_iValue, p_iLen);
}

int callMemberFunc::iTest_iConstParamFunc_vir(const char* p_cStr, const int p_iValue)
{
	return m_pObj->iConstParamFunc_vir(p_cStr, p_iValue);
}

int callMemberFunc::iTest_pcOutputValueByReference_vir(const char* p_cStr, int& p_iLen)
{
	m_pObj->pcOutputValueByReference_vir(p_cStr, p_iLen);
	return 0;
}
