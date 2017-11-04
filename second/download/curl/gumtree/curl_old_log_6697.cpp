fputs(
"              (FTP) Tell curl to disable the use of the EPRT and LPRT commands\n"
"              when doing active FTP transfers. Curl will normally always first\n"
"              attempt to use EPRT, then LPRT before using PORT, but with  this\n"
"              option,  it  will  use PORT right away. EPRT and LPRT are exten-\n"
"              sions to the original FTP protocol, and  may  not  work  on  all\n"
"              servers, but they enable more functionality in a better way than\n"
, stdout);