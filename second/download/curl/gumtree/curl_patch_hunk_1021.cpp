 "\n"
 "              Example:\n"
 "\n"
 "              --proto-default https ftp.mozilla.org\n"
 "                     https://ftp.mozilla.org\n"
 "\n"
-, stdout);
- fputs(
 "       An  unknown or unsupported protocol causes error CURLE_UNSUPPORTED_PRO-\n"
 "       TOCOL.\n"
 "\n"
+, stdout);
+ fputs(
 "       This option does not change the default proxy protocol (http).\n"
 "\n"
 "       Without this option curl would make a guess  based  on  the  host,  see\n"
 "       --url for details.\n"
 "\n"
 "       (Added in 7.45.0)\n"
