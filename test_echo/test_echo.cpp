#include <iostream>
#include <string>
#include "../proto/echo.pb.h"

extern void test_general();
extern void test_relection();
extern void test_rpc();

int main() {
	test_general();
	test_relection();
	test_rpc();
	return 0;
}