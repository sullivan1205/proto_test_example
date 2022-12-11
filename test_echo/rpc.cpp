#include <sstream>
#include "../proto/echo.pb.h"

class MyRpcControllerImpl: public google::protobuf::RpcController {
  public:
    virtual void Reset() override {
      std::cout << "MyRpcController::Reset" << std::endl;
    }
    virtual bool Failed() const override {
      std::cout << "MyRpcController::Failed" << std::endl;
      return false;
    }
    virtual std::string ErrorText() const override {
      std::cout << "MyRpcController::ErrorText" << std::endl;
      return "";
	}
    virtual void StartCancel() override {
      std::cout << "MyRpcController::StartCancel" << std::endl;
    }
    virtual void SetFailed(const std::string& reason) override {
      std::cout << "MyRpcController::SetFailed" << std::endl;
    }
    virtual bool IsCanceled() const override {
      std::cout << "MyRpcController::IsCanceled" << std::endl;
      return false;
    }
    virtual void NotifyOnCancel(google::protobuf::Closure* callback) override {
      std::cout << "MyRpcController::NotifyOnCancel" << std::endl;
    }
};

class MyRpcChannelImpl: public google::protobuf::RpcChannel {
  public:
  	void init() {}
    virtual void CallMethod(const google::protobuf::MethodDescriptor* method,
                            google::protobuf::RpcController* controller,
                            const google::protobuf::Message* request,
                            google::protobuf::Message* response,
                            google::protobuf::Closure* done) override {
      auto req = dynamic_cast<self::EchoRequest*>(
                             const_cast<google::protobuf::Message*>(request));
      auto rsp = dynamic_cast<self::EchoResponse*>(response);
      std::ostringstream oss;
      oss << "I have sent <querytype:{" << req->querytype()
          << "}, payload:{" << req->payload() << "}";
      std::string rcv = oss.str();
      rsp->set_code(0);
      rsp->set_msg(rcv);
    }
};

class MyEchoServiceImpl: public self::EchoService {
  public:
    virtual void Echo(google::protobuf::RpcController* cntl,
                      const self::EchoRequest* request,
                      self::EchoResponse* response,
                      google::protobuf::Closure* done) override {
      std::ostringstream oss;
      oss << "I have received <querytype:{" << request->querytype()
          << "}, payload:{" << request->payload() << "}";
      std::string rcv = oss.str();
      std::cout << "MyEchoServiceImpl::recieve request|" << rcv << std::endl;
      response->set_code(0);
      response->set_msg(rcv);
      done->Run();
  }
  void OnCallbak(google::protobuf::Message* request,
                 google::protobuf::Message* response) {
  	  std::cout << "MyEchoServiceImpl::OnCallbak: response|<code:"
  	            << dynamic_cast<self::EchoResponse*>(response)->code() << ", msg:"
  		        << dynamic_cast<self::EchoResponse*>(response)->msg() << ">"
  		        << std::endl;
  }
};

static void rpc_server() {
  std::cout << "  === START RPC SERVER ===" << std::endl;
  MyEchoServiceImpl svc;
  MyRpcControllerImpl cntl;
  self::EchoRequest request;
  self::EchoResponse response;

  request.set_querytype(self::SECONDARY);
  request.set_payload("rpc_server::request::payload");

  auto req_msg = dynamic_cast<google::protobuf::Message*>(&request);
  auto rsp_msg = dynamic_cast<google::protobuf::Message*>(&response);

  google::protobuf::Closure* done
  	= google::protobuf::NewCallback(&svc,
            &MyEchoServiceImpl::OnCallbak,
            req_msg,
            rsp_msg);

  svc.Echo(&cntl, &request, &response, done);
  std::cout << "  === END RPC SERVER ===" << std::endl;
}

static void rpc_client() {
  std::cout << "  === START RPC CLIENT ===" << std::endl;
  MyRpcControllerImpl cntl;
  self::EchoRequest request;
  self::EchoResponse response;

  request.set_querytype(self::SECONDARY);
  request.set_payload("rpc_client::request::payload");

  MyRpcChannelImpl channel;
  channel.init();
  self::EchoService_Stub stub(&channel);
  stub.Echo(&cntl, &request, &response, nullptr);
  std::cout << "rpc_client::response<code:" << response.code()
            << ",msg:" << response.msg() << ">" << std::endl;
  std::cout << "  === END RPC CLIENT ===" << std::endl;
}

void test_rpc() {
    std::cout << "=== END TEST RPC ===" << std::endl;
    rpc_server();
    rpc_client();
    std::cout << "=== END TEST RPC ===" << std::endl << std::endl;
}