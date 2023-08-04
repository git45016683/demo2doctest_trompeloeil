// demo2doctest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#ifndef TROMPELOEIL_DOCTEST_HPP_
#define TROMPELOEIL_DOCTEST_HPP_

#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "trompeloeil.hpp"
#include "callMemberFunc.h"


using trompeloeil::eq;
using trompeloeil::_;


// ------------------ doctest --------------------

int fact(int n) {
	return (n <= 1) ? n : (fact(n - 1) * n);
}


TEST_CASE("demo2doctest") {
	CHECK(fact(1) == 1);
	CHECK(fact(2) == 2);
}


// ------------------ doctest + trompeloeil mock class function --------------------
class memberFuncMock {
public:
	MAKE_MOCK1(vOutputValueByPointer, void(char*));
	MAKE_MOCK2(bOutputRet, bool(int, int));
	MAKE_MOCK2(iConstParamFunc, void(const char*, const int));
	MAKE_MOCK2(pcOutputValueByReference, void(const char*, int&));
	MAKE_MOCK1(vOutputValueByPointer_vir, void(char*));
	MAKE_MOCK2(bOutputRet_vir, bool(int, int));
	MAKE_MOCK2(iConstParamFunc_vir, void(const char*, const int));
	MAKE_MOCK2(pcOutputValueByReference_vir, void(const char*, int&));
};
memberFuncMock memberMock;

callMemberFunc* g_pCallMemberFunc = new callMemberFunc();

int funcCall_OutputValueByPointer(char* p_pcStr) {
	int l_iRet = -1;
	char l_acStr[256] = {0};
	l_iRet = g_pCallMemberFunc->iTest_OutputValueByPointer(l_acStr);
	memcpy(p_pcStr, l_acStr, 256);
	return l_iRet;
}

TEST_CASE("demo2mockMemberFunc0") {
	char* l_pStr = new char[256];
	memcpy(l_pStr, "HELLOWORLD", strlen("HELLOWORLD"));
	REQUIRE_CALL(memberMock, vOutputValueByPointer(_)).LR_SIDE_EFFECT(memcpy(_1, l_pStr, strlen(l_pStr)));

	char l_acStr[256] = { 0 };
	int l_iRet = funcCall_OutputValueByPointer(l_acStr);
	CHECK(l_iRet == 0);
	CHECK(memcmp(l_acStr, "HELLOWORLD", strlen("HELLOWORLD") == 0));
}

//int main()
//{
//    std::cout << "Hello World!\n";
//}

#endif  // TROMPELOEIL_DOCTEST_HPP_
