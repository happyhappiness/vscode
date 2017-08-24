@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -22,7 +22,8 @@
 
 #include "curl_setup.h"
 
-#if defined(USE_NTLM) && defined(NTLM_WB_ENABLED)
+#if !defined(CURL_DISABLE_HTTP) && defined(USE_NTLM) && \
+    defined(NTLM_WB_ENABLED)
 
 /*
  * NTLM details:
@@ -50,12 +51,10 @@
 #include "curl_ntlm_wb.h"
 #include "url.h"
 #include "strerror.h"
-#include "curl_memory.h"
-
-#define _MPRINTF_REPLACE /* use our functions only */
-#include <curl/mprintf.h>
+#include "curl_printf.h"
 
-/* The last #include file should be: */
+/* The last #include files should be: */
+#include "curl_memory.h"
 #include "memdebug.h"
 
 #if DEBUG_ME
@@ -106,9 +105,9 @@ void Curl_ntlm_wb_cleanup(struct connectdata *conn)
     conn->ntlm_auth_hlpr_pid = 0;
   }
 
-  Curl_safefree(conn->challenge_header);
+  free(conn->challenge_header);
   conn->challenge_header = NULL;
-  Curl_safefree(conn->response_header);
+  free(conn->response_header);
   conn->response_header = NULL;
 }
 
@@ -245,13 +244,13 @@ static CURLcode ntlm_wb_init(struct connectdata *conn, const char *userp)
   sclose(sockfds[1]);
   conn->ntlm_auth_hlpr_socket = sockfds[0];
   conn->ntlm_auth_hlpr_pid = child_pid;
-  Curl_safefree(domain);
-  Curl_safefree(ntlm_auth_alloc);
+  free(domain);
+  free(ntlm_auth_alloc);
   return CURLE_OK;
 
 done:
-  Curl_safefree(domain);
-  Curl_safefree(ntlm_auth_alloc);
+  free(domain);
+  free(ntlm_auth_alloc);
   return CURLE_REMOTE_ACCESS_DENIED;
 }
 
@@ -293,7 +292,7 @@ static CURLcode ntlm_wb_response(struct connectdata *conn,
     len_out += size;
     if(buf[len_out - 1] == '\n') {
       buf[len_out - 1] = '\0';
-      goto wrfinish;
+      break;
     }
     newbuf = realloc(buf, len_out + NTLM_BUFSIZE);
     if(!newbuf) {
@@ -302,13 +301,12 @@ static CURLcode ntlm_wb_response(struct connectdata *conn,
     }
     buf = newbuf;
   }
-  goto done;
-wrfinish:
+
   /* Samba/winbind installed but not configured */
   if(state == NTLMSTATE_TYPE1 &&
      len_out == 3 &&
      buf[0] == 'P' && buf[1] == 'W')
-    return CURLE_REMOTE_ACCESS_DENIED;
+    goto done;
   /* invalid response */
   if(len_out < 4)
     goto done;
@@ -391,12 +389,12 @@ CURLcode Curl_output_ntlm_wb(struct connectdata *conn,
     if(res)
       return res;
 
-    Curl_safefree(*allocuserpwd);
+    free(*allocuserpwd);
     *allocuserpwd = aprintf("%sAuthorization: %s\r\n",
                             proxy ? "Proxy-" : "",
                             conn->response_header);
     DEBUG_OUT(fprintf(stderr, "**** Header %s\n ", *allocuserpwd));
-    Curl_safefree(conn->response_header);
+    free(conn->response_header);
     conn->response_header = NULL;
     break;
   case NTLMSTATE_TYPE2:
@@ -409,7 +407,7 @@ CURLcode Curl_output_ntlm_wb(struct connectdata *conn,
     if(res)
       return res;
 
-    Curl_safefree(*allocuserpwd);
+    free(*allocuserpwd);
     *allocuserpwd = aprintf("%sAuthorization: %s\r\n",
                             proxy ? "Proxy-" : "",
                             conn->response_header);
@@ -421,15 +419,13 @@ CURLcode Curl_output_ntlm_wb(struct connectdata *conn,
   case NTLMSTATE_TYPE3:
     /* connection is already authenticated,
      * don't send a header in future requests */
-    if(*allocuserpwd) {
-      free(*allocuserpwd);
-      *allocuserpwd=NULL;
-    }
+    free(*allocuserpwd);
+    *allocuserpwd=NULL;
     authp->done = TRUE;
     break;
   }
 
   return CURLE_OK;
 }
 
-#endif /* USE_NTLM && NTLM_WB_ENABLED */
+#endif /* !CURL_DISABLE_HTTP && USE_NTLM && NTLM_WB_ENABLED */