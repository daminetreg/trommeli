// hello.cc
#include <node.h>
#include <cling/Interpreter/Interpreter.h>
//#include <cling/UserInterface/UserInterface.h>
//#include <cling/MetaProcessor/MetaProcessor.h>
#include <cling/Interpreter/Value.h>
#include <cling/Interpreter/Interpreter.h>
#include <cling/Interpreter/Value.h>
#include <cling/Utils/Casting.h>
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

static std::vector<double>* plotted_;

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


cling::Interpreter* get_interp() {
  static int argc = 2;
  static const char* argv[2] = {"cling", "-I/home/daminetreg/workspace/trommeli/cling/src/tools/cling/include/" };

  // cling
  static cling::Interpreter Interp(argc, argv);

  return &Interp;
}

/*cling::UserInterface* get_cling() {
  //const cling::InvocationOptions& Opts = Interp.getOptions();
  static cling::UserInterface Ui(*get_interp());
  return &Ui;
}*/

void prepare(const FunctionCallbackInfo<Value>& args) {

  auto& interp = *get_interp();

  std::string Line = "#include <iostream>";
  cling::Interpreter::CompilationResult compRes;

  /*int indent =*/ interp.process(Line);

  Line = R"(std::cout << "hello from cling embedded in Electron" << std::endl;)";
  /*indent =*/ interp.process(Line);

  Line = "#include <vector>";
  interp.process(Line);
  //interp.declare("static std::vector<double> plotted;");
  Line = "std::vector<double> plotted(11);";
  interp.process(Line);

  Line = "#include <algorithm>";
  interp.process(Line);

  Line = " std::generate(plotted.begin(), plotted.end(), [](){return std::rand() % 43; });";
  interp.process(Line);

  //Line = "std::vector< double > plotted(10);";
  //interp.process(Line, compRes);

  //Line = "std::generate_n(plotted.begin(), plotted.end(), [](){ return 0; });";
  //interp.process(Line, compRes);

  cling::Value plotted_ptr;
  Line = "&plotted;";
  interp.process(Line, &plotted_ptr);
  plotted_ = reinterpret_cast<std::vector<double>*>(plotted_ptr.getPtr());
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

  auto& interp = *get_interp();

  std::string Line (*v8::String::Utf8Value(args[0]->ToString()));
  cling::Interpreter::CompilationResult compRes;
  cling::Value val;
  interp.process(Line, &val);

  // Node stuffs
  //args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

Handle<Array> NewPointArray(Isolate* isolate, double x, double y, double z) {

  // We will be creating temporary handles so we use a handle scope.
  HandleScope handle_scope(isolate);

  // Create a new empty array.
  Handle<Array> array = Array::New(isolate, 1);

  // Return an empty result if there was an error creating the array.
  if (array.IsEmpty())
    return Handle<Array>();

  // Fill out the values
  /*array->Set(0, Number::New(isolate, x));*/
  array->Set(1, Number::New(isolate, y));
  /*array->Set(2, Number::New(isolate, z));*/

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
  size_t x = (size_t)args[0]->NumberValue();
  
  auto value  = NewPointArray(isolate, 
    0.1 * x,
    plotted_->at(x),
    //0.1 * x + sin(x),
    0.1*x + cos(x)
  );
  //Local<Number> num = Number::New(isolate, value);

  // Set the return value (using the passed in
  // FunctionCallbackInfo<Value>&)
  args.GetReturnValue().Set(value);
}

void PlotSize(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  auto& interp = *get_interp();
  cling::Value plotted_ptr;
  std::string Line = "&plotted;";
  interp.process(Line, &plotted_ptr);
  auto* plotted_ = reinterpret_cast<std::vector<double>*>(plotted_ptr.getPtr());


  Local<Number> value = Number::New(isolate, plotted_->size());

  // Set the return value (using the passed in
  // FunctionCallbackInfo<Value>&)
  args.GetReturnValue().Set(value);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "prepare", prepare);
  NODE_SET_METHOD(exports, "execute", ExecuteFunction);
  NODE_SET_METHOD(exports, "plot_function", PlotFunction);
  NODE_SET_METHOD(exports, "plot_size", PlotSize);
}

NODE_MODULE(cling_node, init)

}  // namespace demo


