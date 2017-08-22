@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -35,10 +35,7 @@
 #include "progress.h"
 #include "non-ascii.h"
 #include "connect.h"
-
-#define _MPRINTF_REPLACE /* use our functions only */
-#include <curl/mprintf.h>
-
+#include "curl_printf.h"
 #include "curlx.h"
 
 #include "curl_memory.h"
@@ -71,10 +68,11 @@ CURLcode Curl_proxy_connect(struct connectdata *conn)
     conn->data->req.protop = &http_proxy;
     connkeep(conn, "HTTP proxy CONNECT");
     result = Curl_proxyCONNECT(conn, FIRSTSOCKET,
-                               conn->host.name, conn->remote_port);
+                               conn->host.name, conn->remote_port, FALSE);
     conn->data->req.protop = prot_save;
     if(CURLE_OK != result)
       return result;
+    Curl_safefree(conn->allocptr.proxyuserpwd);
 #else
     return CURLE_NOT_BUILT_IN;
 #endif
@@ -87,12 +85,16 @@ CURLcode Curl_proxy_connect(struct connectdata *conn)
  * Curl_proxyCONNECT() requires that we're connected to a HTTP proxy. This
  * function will issue the necessary commands to get a seamless tunnel through
  * this proxy. After that, the socket can be used just as a normal socket.
+ *
+ * 'blocking' set to TRUE means that this function will do the entire CONNECT
+ * + response in a blocking fashion. Should be avoided!
  */
 
 CURLcode Curl_proxyCONNECT(struct connectdata *conn,
                            int sockindex,
                            const char *hostname,
-                           int remote_port)
+                           int remote_port,
+                           bool blocking)
 {
   int subversion=0;
   struct SessionHandle *data=conn->data;
@@ -123,13 +125,11 @@ CURLcode Curl_proxyCONNECT(struct connectdata *conn,
       infof(data, "Establish HTTP proxy tunnel to %s:%hu\n",
             hostname, remote_port);
 
-      if(data->req.newurl) {
         /* This only happens if we've looped here due to authentication
            reasons, and we don't really use the newly cloned URL here
            then. Just free() it. */
-        free(data->req.newurl);
-        data->req.newurl = NULL;
-      }
+      free(data->req.newurl);
+      data->req.newurl = NULL;
 
       /* initialize a dynamic send-buffer */
       req_buffer = Curl_add_buffer_init();
@@ -139,7 +139,7 @@ CURLcode Curl_proxyCONNECT(struct connectdata *conn,
 
       host_port = aprintf("%s:%hu", hostname, remote_port);
       if(!host_port) {
-        free(req_buffer);
+        Curl_add_buffer_free(req_buffer);
         return CURLE_OUT_OF_MEMORY;
       }
 
@@ -148,7 +148,7 @@ CURLcode Curl_proxyCONNECT(struct connectdata *conn,
 
       free(host_port);
 
-      if(CURLE_OK == result) {
+      if(!result) {
         char *host=(char *)"";
         const char *proxyconn="";
         const char *useragent="";
@@ -159,15 +159,15 @@ CURLcode Curl_proxyCONNECT(struct connectdata *conn,
                   hostname, conn->bits.ipv6_ip?"]":"",
                   remote_port);
         if(!hostheader) {
-          free(req_buffer);
+          Curl_add_buffer_free(req_buffer);
           return CURLE_OUT_OF_MEMORY;
         }
 
         if(!Curl_checkProxyheaders(conn, "Host:")) {
           host = aprintf("Host: %s\r\n", hostheader);
           if(!host) {
             free(hostheader);
-            free(req_buffer);
+            Curl_add_buffer_free(req_buffer);
             return CURLE_OUT_OF_MEMORY;
           }
         }
@@ -197,14 +197,14 @@ CURLcode Curl_proxyCONNECT(struct connectdata *conn,
           free(host);
         free(hostheader);
 
-        if(CURLE_OK == result)
+        if(!result)
           result = Curl_add_custom_headers(conn, TRUE, req_buffer);
 
-        if(CURLE_OK == result)
+        if(!result)
           /* CRLF terminate the request */
           result = Curl_add_bufferf(req_buffer, "\r\n");
 
-        if(CURLE_OK == result) {
+        if(!result) {
           /* Send the connect request to the proxy */
           /* BLOCKING */
           result =
@@ -216,7 +216,7 @@ CURLcode Curl_proxyCONNECT(struct connectdata *conn,
           failf(data, "Failed sending CONNECT to proxy");
       }
 
-      Curl_safefree(req_buffer);
+      Curl_add_buffer_free(req_buffer);
       if(result)
         return result;
 
@@ -229,12 +229,14 @@ CURLcode Curl_proxyCONNECT(struct connectdata *conn,
       return CURLE_RECV_ERROR;
     }
 
-    if(0 == Curl_socket_ready(tunnelsocket, CURL_SOCKET_BAD, 0))
-      /* return so we'll be called again polling-style */
-      return CURLE_OK;
-    else {
-      DEBUGF(infof(data,
-                   "Read response immediately from proxy CONNECT\n"));
+    if(!blocking) {
+      if(0 == Curl_socket_ready(tunnelsocket, CURL_SOCKET_BAD, 0))
+        /* return so we'll be called again polling-style */
+        return CURLE_OK;
+      else {
+        DEBUGF(infof(data,
+               "Read response immediately from proxy CONNECT\n"));
+      }
     }
 
     /* at this point, the tunnel_connecting phase is over. */
@@ -252,7 +254,6 @@ CURLcode Curl_proxyCONNECT(struct connectdata *conn,
 
       nread=0;
       perline=0;
-      keepon=TRUE;
 
       while((nread<BUFSIZE) && (keepon && !error)) {
 
@@ -286,7 +287,7 @@ CURLcode Curl_proxyCONNECT(struct connectdata *conn,
               /* proxy auth was requested and there was proxy auth available,
                  then deem this as "mere" proxy disconnect */
               conn->bits.proxy_connect_closed = TRUE;
-              infof(data, "Proxy CONNECT connection closed");
+              infof(data, "Proxy CONNECT connection closed\n");
             }
             else {
               error = SELECT_ERROR;
@@ -468,7 +469,7 @@ CURLcode Curl_proxyCONNECT(struct connectdata *conn,
 
                     result = Curl_http_input_auth(conn, proxy, auth);
 
-                    Curl_safefree(auth);
+                    free(auth);
 
                     if(result)
                       return result;
@@ -555,11 +556,8 @@ CURLcode Curl_proxyCONNECT(struct connectdata *conn,
       infof(data, "Connect me again please\n");
     }
     else {
-      if(data->req.newurl) {
-        /* this won't be used anymore for the CONNECT so free it now */
-        free(data->req.newurl);
-        data->req.newurl = NULL;
-      }
+      free(data->req.newurl);
+      data->req.newurl = NULL;
       /* failure, close this connection to avoid re-use */
       connclose(conn, "proxy CONNECT failure");
       Curl_closesocket(conn, conn->sock[sockindex]);