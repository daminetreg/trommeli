// hello.cc
#include <node.h>
#include <cling/Interpreter/Interpreter.h>
#include <cling/UserInterface/UserInterface.h>
#include <cling/MetaProcessor/MetaProcessor.h>


namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {

  int argc = 1;
  const char* argv[1] = {"cling"};

  // cling
  cling::Interpreter Interp(argc, argv);
  //const cling::InvocationOptions& Opts = Interp.getOptions();
  cling::UserInterface Ui(Interp);

  std::string Line = "#include <iostream>";
  cling::Interpreter::CompilationResult compRes;

  /*int indent =*/ Ui.getMetaProcessor()->process(Line, compRes);

  Line = R"(std::cout << "hello world" << std::endl;)";
  /*indent =*/ Ui.getMetaProcessor()->process(Line, compRes);

  // Node stuffs
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(cling_node, init)

}  // namespace demo


