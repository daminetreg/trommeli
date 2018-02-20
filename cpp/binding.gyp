{
  "targets": [
    {
      "target_name": "cling_node",
      "sources": [ "main.cpp" ],
      "cflags" :  ["-std=c++11", "-fPIC", "-DPIC"],
      'cflags_cc!': [ '-std=-std=gnu++0x', '-fno-rtti', '-fno-exceptions' ],
      'include_dirs': [
        '/opt/softwares/cling_2018-02-17_ubuntu16/include',
      ],
      'link_settings': {
        'libraries': [
          "-fPIC",
          '-L/home/daminetreg/workspace/trommeli/cling/src/build/lib',
          '-lcling'
        ],
      }
    }
  ]
}
