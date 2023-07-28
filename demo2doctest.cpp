// demo2doctest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#ifndef TROMPELOEIL_DOCTEST_HPP_
#define TROMPELOEIL_DOCTEST_HPP_

#include <iostream>
#include "freeFuncHeader.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "trompeloeil.hpp"


#define TRY_TROMPELOEIL 1
using trompeloeil::eq;
using trompeloeil::_;

int fact(int n) {
	return (n <= 1) ? n : (fact(n - 1) * n);
}


TEST_CASE("demo2doctest") {
	CHECK(fact(1) == 1);
	CHECK(fact(2) == 2);
}



#if TRY_TROMPELOEIL


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

//try mock iDownLoad with trompeloeil
//int iDownLoad(){
//	return -1;
//}

#endif // TRY_TROMPELOEIL

//int main()
//{
//    std::cout << "Hello World!\n";
//}

#endif  // TROMPELOEIL_DOCTEST_HPP_