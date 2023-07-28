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

//extern "C" {
	int iDownLoad(){
		return freeMock.iDownLoad();
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