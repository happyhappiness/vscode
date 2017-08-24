@@ -1,8 +1,8 @@
 /* GSSAPI/krb5 support for FTP - loosely based on old krb4.c
  *
- * Copyright (c) 1995, 1996, 1997, 1998, 1999, 2013 Kungliga Tekniska H�gskolan
+ * Copyright (c) 1995, 1996, 1997, 1998, 1999 Kungliga Tekniska H�gskolan
  * (Royal Institute of Technology, Stockholm, Sweden).
- * Copyright (c) 2004 - 2012 Daniel Stenberg
+ * Copyright (c) 2004 - 2015 Daniel Stenberg
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -34,13 +34,7 @@
 
 #include "curl_setup.h"
 
-#ifndef CURL_DISABLE_FTP
-#ifdef HAVE_GSSAPI
-
-#ifdef HAVE_OLD_GSSMIT
-#define GSS_C_NT_HOSTBASED_SERVICE gss_nt_service_name
-#define NCOMPAT 1
-#endif
+#if defined(HAVE_GSSAPI) && !defined(CURL_DISABLE_FTP)
 
 #ifdef HAVE_NETDB_H
 #include <netdb.h>
@@ -52,13 +46,11 @@
 #include "curl_gssapi.h"
 #include "sendf.h"
 #include "curl_sec.h"
-#include "curl_memory.h"
 #include "warnless.h"
+#include "curl_printf.h"
 
-#define _MPRINTF_REPLACE /* use our functions only */
-#include <curl/mprintf.h>
-
-/* The last #include file should be: */
+/* The last #include files should be: */
+#include "curl_memory.h"
 #include "memdebug.h"
 
 #define LOCAL_ADDR (&conn->local_addr)
@@ -121,18 +113,14 @@ krb5_overhead(void *app_data, int level, int len)
 }
 
 static int
-krb5_encode(void *app_data, const void *from, int length, int level, void **to,
-            struct connectdata *conn UNUSED_PARAM)
+krb5_encode(void *app_data, const void *from, int length, int level, void **to)
 {
   gss_ctx_id_t *context = app_data;
   gss_buffer_desc dec, enc;
   OM_uint32 maj, min;
   int state;
   int len;
 
-  /* shut gcc up */
-  conn = NULL;
-
   /* NOTE that the cast is safe, neither of the krb5, gnu gss and heimdal
    * libraries modify the input buffer in gss_seal()
    */
@@ -240,6 +228,7 @@ krb5_auth(void *app_data, struct connectdata *conn)
                                       &chan,
                                       gssresp,
                                       &output_buffer,
+                                      TRUE,
                                       NULL);
 
       if(gssresp) {
@@ -257,7 +246,8 @@ krb5_auth(void *app_data, struct connectdata *conn)
         result = Curl_base64_encode(data, (char *)output_buffer.value,
                                     output_buffer.length, &p, &base64_sz);
         if(result) {
-          Curl_infof(data,"base64-encoding: %s\n", curl_easy_strerror(result));
+          Curl_infof(data, "base64-encoding: %s\n",
+                     curl_easy_strerror(result));
           ret = AUTH_CONTINUE;
           break;
         }
@@ -289,7 +279,8 @@ krb5_auth(void *app_data, struct connectdata *conn)
                                       (unsigned char **)&_gssresp.value,
                                       &_gssresp.length);
           if(result) {
-            Curl_failf(data,"base64-decoding: %s", curl_easy_strerror(result));
+            Curl_failf(data, "base64-decoding: %s",
+                       curl_easy_strerror(result));
             ret = AUTH_CONTINUE;
             break;
           }
@@ -338,5 +329,4 @@ struct Curl_sec_client_mech Curl_krb5_client_mech = {
     krb5_decode
 };
 
-#endif /* HAVE_GSSAPI */
-#endif /* CURL_DISABLE_FTP */
+#endif /* HAVE_GSSAPI && !CURL_DISABLE_FTP */