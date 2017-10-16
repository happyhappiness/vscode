   /* Warns if this procedure has not been updated when the dupstring enum
      changes.
      We (try to) do it only once: there is no need to issue several times
      the same message; but since threadsafeness is not handled here,
      this may occur (and we don't care!). */
 
-  if (testwarn) {
+  if(testwarn) {
     testwarn = 0;
 
 #ifdef USE_TLS_SRP
-    if ((int) STRING_LAST != (int) STRING_TLSAUTH_PASSWORD + 1)
+    if((int) STRING_LAST != (int) STRING_TLSAUTH_PASSWORD + 1)
 #else
-    if ((int) STRING_LAST != (int) STRING_MAIL_AUTH + 1)
+    if((int) STRING_LAST != (int) STRING_MAIL_AUTH + 1)
 #endif
       curl_mfprintf(stderr,
        "*** WARNING: curl_easy_setopt_ccsid() should be reworked ***\n");
     }
 
   data = (struct SessionHandle *) curl;
