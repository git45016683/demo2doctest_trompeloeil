// demo2doctest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#ifndef TROMPELOEIL_DOCTEST_HPP_
#define TROMPELOEIL_DOCTEST_HPP_

#include <iostream>
#include "freeFuncHeader.h"

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


// ------------------ doctest + trompeloeil mock free function --------------------

class freeFuncMock {
public:
	MAKE_MOCK0(iDownLoad, int());
	MAKE_MOCK1(bOutputValueWithPointer, bool(int*));
	MAKE_MOCK2(vOutputValueWithPointer, void(int*, long*));
};
freeFuncMock freeMock;

int funcCallAPIneedmock() {
	int l_iRet = 0;
	l_iRet = iDownLoad();
	return l_iRet;
}

TEST_CASE("demo2doctestNOTmock") {
	REQUIRE_CALL(freeMock, iDownLoad()).RETURN(-1);
	CHECK(funcCallAPIneedmock() == -1);
}

TEST_CASE("demo2doctestBYmock") {
	REQUIRE_CALL(freeMock, iDownLoad()).RETURN(6);
	CHECK(funcCallAPIneedmock() == 6);
}

int funcCallAPIneedmockWithPointer() {
	int l_iValue2 = -2;
	long l_lValue2 = 0;
	vOutputValueWithPointer(&l_iValue2, &l_lValue2);

	int l_iValue = -1;
	bool l_bRet = bOutputValueWithPointer(&l_iValue);

	int l_iRet = 0;
	if (l_bRet) {
		l_iRet = l_iValue + l_iValue2;
	} else {
		l_iRet = l_iValue2 + l_lValue2;
	}

	return l_iRet;
}

TEST_CASE("demo2doctestBYmockWithPointer") {
	// 方式1，本地引用出参
	int result = 11;
	int iresult2 = 3;
	long lresult2 = 6;
	REQUIRE_CALL(freeMock, bOutputValueWithPointer(_)).LR_SIDE_EFFECT(*_1 = result).RETURN(true);
	REQUIRE_CALL(freeMock, vOutputValueWithPointer(_,_)).LR_SIDE_EFFECT(*_1 = iresult2, *_2 = lresult2);
	// 方式2，魔数直接出参
	//REQUIRE_CALL(freeMock, bOutputValueWithPointer(_)).SIDE_EFFECT(*_1 = 11).RETURN(true);
	//REQUIRE_CALL(freeMock, vOutputValueWithPointer(_, _)).SIDE_EFFECT(*_1 = 3, *_2 = 6);

	CHECK(funcCallAPIneedmockWithPointer() == (11 + 3));
}

//extern "C" {
	int iDownLoad(){
		return freeMock.iDownLoad();
	}	
	bool bOutputValueWithPointer(int* p_iValue){
		return freeMock.bOutputValueWithPointer(p_iValue);
	}	
	void vOutputValueWithPointer(int* p_iValue, long* p_lValue){
		freeMock.vOutputValueWithPointer(p_iValue, p_lValue);
	}
//}



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

callMemberFunc* g_pCallMemberFunc = new callMemberFunc((memberFuncHeader*) & memberMock);

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