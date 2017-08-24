@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -22,7 +22,7 @@
 
 #include "curl_setup.h"
 
-#ifdef USE_NTLM
+#if !defined(CURL_DISABLE_HTTP) && defined(USE_NTLM)
 
 /*
  * NTLM details:
@@ -39,19 +39,18 @@
 #include "curl_ntlm.h"
 #include "curl_ntlm_msgs.h"
 #include "curl_ntlm_wb.h"
+#include "curl_sasl.h"
 #include "url.h"
-#include "curl_memory.h"
-
-#define _MPRINTF_REPLACE /* use our functions only */
-#include <curl/mprintf.h>
+#include "curl_printf.h"
 
 #if defined(USE_NSS)
 #include "vtls/nssg.h"
 #elif defined(USE_WINDOWS_SSPI)
 #include "curl_sspi.h"
 #endif
 
-/* The last #include file should be: */
+/* The last #include files should be: */
+#include "curl_memory.h"
 #include "memdebug.h"
 
 #if DEBUG_ME
@@ -69,12 +68,6 @@ CURLcode Curl_input_ntlm(struct connectdata *conn,
   struct ntlmdata *ntlm;
   CURLcode result = CURLE_OK;
 
-#ifdef USE_NSS
-  result = Curl_nss_force_init(conn->data);
-  if(result)
-    return result;
-#endif
-
   ntlm = proxy ? &conn->proxyntlm : &conn->ntlm;
 
   if(checkprefix("NTLM", header)) {
@@ -84,14 +77,18 @@ CURLcode Curl_input_ntlm(struct connectdata *conn,
       header++;
 
     if(*header) {
-      result = Curl_ntlm_decode_type2_message(conn->data, header, ntlm);
-      if(CURLE_OK != result)
+      result = Curl_sasl_decode_ntlm_type2_message(conn->data, header, ntlm);
+      if(result)
         return result;
 
       ntlm->state = NTLMSTATE_TYPE2; /* We got a type-2 message */
     }
     else {
-      if(ntlm->state == NTLMSTATE_TYPE3) {
+      if(ntlm->state == NTLMSTATE_LAST) {
+        infof(conn->data, "NTLM auth restarted\n");
+        Curl_http_ntlm_cleanup(conn);
+      }
+      else if(ntlm->state == NTLMSTATE_TYPE3) {
         infof(conn->data, "NTLM handshake rejected\n");
         Curl_http_ntlm_cleanup(conn);
         ntlm->state = NTLMSTATE_NONE;
@@ -112,12 +109,11 @@ CURLcode Curl_input_ntlm(struct connectdata *conn,
 /*
  * This is for creating ntlm header output
  */
-CURLcode Curl_output_ntlm(struct connectdata *conn,
-                          bool proxy)
+CURLcode Curl_output_ntlm(struct connectdata *conn, bool proxy)
 {
   char *base64 = NULL;
   size_t len = 0;
-  CURLcode error;
+  CURLcode result;
 
   /* point to the address of the pointer that holds the string to send to the
      server, which is for a plain host or for a HTTP proxy */
@@ -175,38 +171,40 @@ CURLcode Curl_output_ntlm(struct connectdata *conn,
   case NTLMSTATE_TYPE1:
   default: /* for the weird cases we (re)start here */
     /* Create a type-1 message */
-    error = Curl_ntlm_create_type1_message(userp, passwdp, ntlm, &base64,
-                                           &len);
-    if(error)
-      return error;
+    result = Curl_sasl_create_ntlm_type1_message(userp, passwdp, ntlm, &base64,
+                                                 &len);
+    if(result)
+      return result;
 
     if(base64) {
-      Curl_safefree(*allocuserpwd);
+      free(*allocuserpwd);
       *allocuserpwd = aprintf("%sAuthorization: NTLM %s\r\n",
                               proxy ? "Proxy-" : "",
                               base64);
       free(base64);
       if(!*allocuserpwd)
         return CURLE_OUT_OF_MEMORY;
+
       DEBUG_OUT(fprintf(stderr, "**** Header %s\n ", *allocuserpwd));
     }
     break;
 
   case NTLMSTATE_TYPE2:
     /* We already received the type-2 message, create a type-3 message */
-    error = Curl_ntlm_create_type3_message(conn->data, userp, passwdp,
-                                           ntlm, &base64, &len);
-    if(error)
-      return error;
+    result = Curl_sasl_create_ntlm_type3_message(conn->data, userp, passwdp,
+                                                 ntlm, &base64, &len);
+    if(result)
+      return result;
 
     if(base64) {
-      Curl_safefree(*allocuserpwd);
+      free(*allocuserpwd);
       *allocuserpwd = aprintf("%sAuthorization: NTLM %s\r\n",
                               proxy ? "Proxy-" : "",
                               base64);
       free(base64);
       if(!*allocuserpwd)
         return CURLE_OUT_OF_MEMORY;
+
       DEBUG_OUT(fprintf(stderr, "**** %s\n ", *allocuserpwd));
 
       ntlm->state = NTLMSTATE_TYPE3; /* we send a type-3 */
@@ -217,6 +215,9 @@ CURLcode Curl_output_ntlm(struct connectdata *conn,
   case NTLMSTATE_TYPE3:
     /* connection is already authenticated,
      * don't send a header in future requests */
+    ntlm->state = NTLMSTATE_LAST;
+
+  case NTLMSTATE_LAST:
     Curl_safefree(*allocuserpwd);
     authp->done = TRUE;
     break;
@@ -227,22 +228,12 @@ CURLcode Curl_output_ntlm(struct connectdata *conn,
 
 void Curl_http_ntlm_cleanup(struct connectdata *conn)
 {
-#ifdef USE_WINDOWS_SSPI
-  Curl_ntlm_sspi_cleanup(&conn->ntlm);
-  Curl_ntlm_sspi_cleanup(&conn->proxyntlm);
-#elif defined(NTLM_WB_ENABLED)
-  Curl_ntlm_wb_cleanup(conn);
-#else
-  (void)conn;
-#endif
+  Curl_sasl_ntlm_cleanup(&conn->ntlm);
+  Curl_sasl_ntlm_cleanup(&conn->proxyntlm);
 
-#ifndef USE_WINDOWS_SSPI
-  Curl_safefree(conn->ntlm.target_info);
-  conn->ntlm.target_info_len = 0;
-
-  Curl_safefree(conn->proxyntlm.target_info);
-  conn->proxyntlm.target_info_len = 0;
+#if defined(NTLM_WB_ENABLED)
+  Curl_ntlm_wb_cleanup(conn);
 #endif
 }
 
-#endif /* USE_NTLM */
+#endif /* !CURL_DISABLE_HTTP && USE_NTLM */