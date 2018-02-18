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
           '/opt/softwares/cling_2018-02-17_ubuntu16/lib/libcling.so.5',
        ],
      }
    }
  ]
}
