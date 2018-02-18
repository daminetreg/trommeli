// hello.cc
#include <node.h>
#include <cling/Interpreter/Interpreter.h>
#include <cling/UserInterface/UserInterface.h>
#include <cling/MetaProcessor/MetaProcessor.h>

/*

  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libclangFrontendTool.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libclingInterpreter.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libclingMetaProcessor.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libclingUserInterface.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libclingUtils.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libclangDriver.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libclangFrontend.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libclangParse.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libclangSema.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libclangAST.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libclangLex.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libclangSerialization.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libclangCodeGen.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libclangBasic.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libLLVMAnalysis.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libLLVMCore.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libLLVMExecutionEngine.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libLLVMipo.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libLLVMMC.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libLLVMObject.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libLLVMOption.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libLLVMOrcJIT.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libLLVMRuntimeDyld.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libLLVMScalarOpts.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libLLVMSupport.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libLLVMTarget.a',
  '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libLLVMTransformUtils.a'
*/

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {

  int argc = 3;
  const char* argv[3] = {"cling", "-I", "/opt/softwares/cling_2018-02-17_ubuntu16/include/"};

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


