{
  "targets": [
    {
      "target_name": "cling_node",
      "sources": [ "main.cpp" ],
      "cflags" :  ["-std=c++17"],
      'include_dirs': [
        '/opt/softwares/cling_2018-02-17_ubuntu16/include',
      ],
      'link_settings': {
        'libraries': [
          '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libcling.so',
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
        ],
      }
    }
  ]
}
