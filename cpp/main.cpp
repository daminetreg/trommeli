// hello.cc
#include <node.h>
#include <cling/Interpreter/Interpreter.h>
#include <cling/UserInterface/UserInterface.h>
#include <cling/MetaProcessor/MetaProcessor.h>
#include <cmath>

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
using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Handle;
using v8::HandleScope;
using v8::Array;

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

void ExecuteFunction(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  // Check the number of arguments passed.
  if (args.Length() < 1) {
    // Throw an Error that is passed back to JavaScript
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  // Check the argument types
  if (!args[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  static int argc = 3;
  static const char* argv[3] = {"cling", "-I", "/opt/softwares/cling_2018-02-17_ubuntu16/include/"};

  // cling
  static cling::Interpreter Interp(argc, argv);
  //const cling::InvocationOptions& Opts = Interp.getOptions();
  static cling::UserInterface Ui(Interp);

  std::string Line (*v8::String::Utf8Value(args[0]->ToString()));
  cling::Interpreter::CompilationResult compRes;
  /*int indent =*/ Ui.getMetaProcessor()->process(Line, compRes);

  /*indent =*/ Ui.getMetaProcessor()->process(Line, compRes);

  // Node stuffs
  //args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

Handle<Array> NewPointArray(Isolate* isolate, double x, double y, double z) {

  // We will be creating temporary handles so we use a handle scope.
  HandleScope handle_scope(isolate);

  // Create a new empty array.
  Handle<Array> array = Array::New(isolate, 3);

  // Return an empty result if there was an error creating the array.
  if (array.IsEmpty())
    return Handle<Array>();

  // Fill out the values
  array->Set(0, Number::New(isolate, x));
  array->Set(1, Number::New(isolate, y));
  array->Set(2, Number::New(isolate, z));

  // Return the value through Close.
  return array;
}

void PlotFunction(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  // Check the number of arguments passed.
  if (args.Length() < 1) {
    // Throw an Error that is passed back to JavaScript
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  // Check the argument types
  if (!args[0]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  // Perform the operation
  double x = args[0]->NumberValue();
  auto value  = NewPointArray(isolate, 0.1 * x, 0.1 * x + sin(x), 0.1*x + cos(x));
  //Local<Number> num = Number::New(isolate, value);

  // Set the return value (using the passed in
  // FunctionCallbackInfo<Value>&)
  args.GetReturnValue().Set(value);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
  NODE_SET_METHOD(exports, "execute", ExecuteFunction);
  NODE_SET_METHOD(exports, "plot_function", PlotFunction);
}

NODE_MODULE(cling_node, init)

}  // namespace demo


