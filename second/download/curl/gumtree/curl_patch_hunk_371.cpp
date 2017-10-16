      the same message; but since threadsafeness is not handled here,
      this may occur (and we don't care!). */
 
   if (testwarn) {
     testwarn = 0;
 
-    if ((int) STRING_LAST != (int) STRING_PROXYPASSWORD + 1)
+    if ((int) STRING_LAST != (int) STRING_SOCKS5_GSSAPI_SERVICE + 1)
       curl_mfprintf(stderr,
        "*** WARNING: curl_easy_setopt_ccsid() should be reworked ***\n");
     }
 
   data = (struct SessionHandle *) curl;
   va_start(arg, tag);
