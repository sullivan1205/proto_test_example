#include <cstdio>
#include <iostream>
#include "../proto/serialize.pb.h"

//输出十六进制编码
static void dump_hexstring(const std::string& tag, const std::string& data) {
  printf("%s:\n", tag.c_str());
  for (size_t i = 0; i < data.size(); ++i) {
    printf("%02x ", (unsigned char)data[i]);
  }
  printf("\n\n");
}

static void test_1() {
  mytest::Test t1;
  t1.set_i32(300);
  std::string buf;
  t1.SerializeToString(&buf);
  dump_hexstring("==== test_1 ====", buf);
}

int main() {
  test_1();
  return 0;
}