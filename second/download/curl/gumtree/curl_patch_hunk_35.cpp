 "  (enforce ASCII) flag.\n"
 "\n"
 "ENVIRONMENT VARIABLES\n"
 "\n"
 "  Curl reads and understands the following environment variables:\n"
 "\n"
-);
- puts(
+, stdout);
+ fputs(
 "        http_proxy, HTTPS_PROXY, FTP_PROXY, GOPHER_PROXY\n"
 "\n"
 "  They should be set for protocol-specific proxies. General proxy should be\n"
 "  set with\n"
 "        \n"
 "        ALL_PROXY\n"
