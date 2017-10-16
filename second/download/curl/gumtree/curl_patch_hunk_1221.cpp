   {"HTTPS-proxy",    CURL_VERSION_HTTPS_PROXY}
 };
 
 void tool_help(void)
 {
   int i;
-  for(i = 0; helptext[i]; i++) {
-    puts(helptext[i]);
+  puts("Usage: curl [options...] <url>");
+  for(i = 0; helptext[i].opt; i++) {
+    printf(" %-19s %s\n", helptext[i].opt, helptext[i].desc);
 #ifdef PRINT_LINES_PAUSE
     if(i && ((i % PRINT_LINES_PAUSE) == 0))
       tool_pressanykey();
 #endif
   }
 }
 
 void tool_version_info(void)
 {
   const char *const *proto;
 
   printf(CURL_ID "%s\n", curl_version());
+#ifdef CURL_PATCHSTAMP
+  printf("Release-Date: %s, security patched: %s\n",
+         LIBCURL_TIMESTAMP, CURL_PATCHSTAMP);
+#else
+  printf("Release-Date: %s\n", LIBCURL_TIMESTAMP);
+#endif
   if(curlinfo->protocols) {
     printf("Protocols: ");
     for(proto = curlinfo->protocols; *proto; ++proto) {
       printf("%s ", *proto);
     }
     puts(""); /* newline */
