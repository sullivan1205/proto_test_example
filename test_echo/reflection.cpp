#include "../proto/echo.pb.h"

void test_relection() {
	std::cout << "=== START TEST REFLECTION ===" << std::endl;
	std::string type_name = self::EchoRequest::descriptor()->full_name();
	std::cout << "type_name: " << type_name << std::endl;

	const google::protobuf::Descriptor* descriptor 
		= google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
	const google::protobuf::Message* prototype
		= google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
	google::protobuf::Message* req_msg = prototype->New();
	const google::protobuf::Reflection* req_msg_ref
		= req_msg->GetReflection();
	const google::protobuf::FieldDescriptor *req_msg_ref_field_payload
		= descriptor->FindFieldByName("payload");

	std::cout << "ref_req_msg_payload: "
			  << req_msg_ref->GetString(*req_msg, req_msg_ref_field_payload)
			  << std::endl;
	req_msg_ref->SetString(req_msg, req_msg_ref_field_payload, "my payload");
	std::cout << "ref_req_msg_payload: "
			  << req_msg_ref->GetString(*req_msg, req_msg_ref_field_payload)
			  << std::endl;
	std::cout << "=== END TEST REFLECTION ===" << std::endl << std::endl;
}