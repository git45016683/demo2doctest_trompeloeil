// demo2doctest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#ifndef TROMPELOEIL_DOCTEST_HPP_
#define TROMPELOEIL_DOCTEST_HPP_

#include <iostream>
#include "freeFuncHeader.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "doctest/trompeloeil.hpp"




int fact(int n) {
	return (n <= 1) ? n : (fact(n - 1) * n);
}


TEST_CASE("demo2doctest") {
	CHECK(fact(1) == 1);
	CHECK(fact(2) == 2);
}


class freeFuncMock {
public:
	MAKE_MOCK0(iDownLoad, int());
};


int funcCallAPIneedmock() {
	int l_iRet = 0;
	l_iRet = iDownLoad();
	return l_iRet;
}


TEST_CASE("demo2doctestNOTmock") {
	CHECK(funcCallAPIneedmock() == -1);
}

extern freeFuncMock freeMock;

TEST_CASE("demo2doctestBYmock") {

	CHECK(funcCallAPIneedmock() == 6);
}

extern "C" {
	int iDownLoad(){
		return freeMock.iDownLoad();
	}
}

//try mock iDownLoad with trompeloeil
//int iDownLoad(){
//	return -1;
//}

//int main()
//{
//    std::cout << "Hello World!\n";
//}

#endif  // TROMPELOEIL_DOCTEST_HPP_