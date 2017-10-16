     if((int) STRING_LASTZEROTERMINATED != (int) STRING_UNIX_SOCKET_PATH + 1 ||
        (int) STRING_LAST != (int) STRING_COPYPOSTFIELDS + 1)
       curl_mfprintf(stderr,
        "*** WARNING: curl_easy_setopt_ccsid() should be reworked ***\n");
     }
 
-  data = (struct SessionHandle *) curl;
+  data = (struct Curl_easy *) curl;
   va_start(arg, tag);
 
   switch (tag) {
 
   case CURLOPT_CAINFO:
   case CURLOPT_CAPATH:
