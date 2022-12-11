#include "../proto/echo.pb.h"

extern void test_general() {
	std::cout << "=== START TEST GENERAL ===" << std::endl;
	self::EchoRequest req;
	req.set_querytype(self::SECONDARY);
	req.set_payload("this is a payload");

	std::string req_body;
	req.SerializeToString(&req_body);

	self::EchoRequest req_rcv;
	req_rcv.ParseFromString(req_body);
	std::cout << "req.querytype[" << req.querytype() << "], "
			  << "req_rcv.querytype[" << req_rcv.querytype() << "]" << std::endl
			  << "req.payload[" << req.payload() << "], "
			  << "req_rcv.payload[" << req_rcv.payload() << "]"<< std::endl;
	std::cout << "=== END TEST GENERAL ===" << std::endl << std::endl;
}