@@ -5,11 +5,11 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
- * are also available at http://curl.haxx.se/docs/copyright.html.
+ * are also available at https://curl.haxx.se/docs/copyright.html.
  *
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
@@ -35,11 +35,11 @@
 #include "progress.h"
 #include "non-ascii.h"
 #include "connect.h"
-#include "curl_printf.h"
 #include "curlx.h"
 
+/* The last 3 #include files should be in this order */
+#include "curl_printf.h"
 #include "curl_memory.h"
-/* The last #include file should be: */
 #include "memdebug.h"
 
 CURLcode Curl_proxy_connect(struct connectdata *conn)
@@ -49,6 +49,8 @@ CURLcode Curl_proxy_connect(struct connectdata *conn)
     /* for [protocol] tunneled through HTTP proxy */
     struct HTTP http_proxy;
     void *prot_save;
+    const char *hostname;
+    int remote_port;
     CURLcode result;
 
     /* BLOCKING */
@@ -67,8 +69,16 @@ CURLcode Curl_proxy_connect(struct connectdata *conn)
     memset(&http_proxy, 0, sizeof(http_proxy));
     conn->data->req.protop = &http_proxy;
     connkeep(conn, "HTTP proxy CONNECT");
-    result = Curl_proxyCONNECT(conn, FIRSTSOCKET,
-                               conn->host.name, conn->remote_port, FALSE);
+    if(conn->bits.conn_to_host)
+      hostname = conn->conn_to_host.name;
+    else
+      hostname = conn->host.name;
+    if(conn->bits.conn_to_port)
+      remote_port = conn->conn_to_port;
+    else
+      remote_port = conn->remote_port;
+    result = Curl_proxyCONNECT(conn, FIRSTSOCKET, hostname,
+                               remote_port, FALSE);
     conn->data->req.protop = prot_save;
     if(CURLE_OK != result)
       return result;
@@ -97,7 +107,7 @@ CURLcode Curl_proxyCONNECT(struct connectdata *conn,
                            bool blocking)
 {
   int subversion=0;
-  struct SessionHandle *data=conn->data;
+  struct Curl_easy *data=conn->data;
   struct SingleRequest *k = &data->req;
   CURLcode result;
   curl_socket_t tunnelsocket = conn->sock[sockindex];
@@ -150,13 +160,17 @@ CURLcode Curl_proxyCONNECT(struct connectdata *conn,
 
       if(!result) {
         char *host=(char *)"";
-        const char *proxyconn="";
         const char *useragent="";
         const char *http = (conn->proxytype == CURLPROXY_HTTP_1_0) ?
           "1.0" : "1.1";
-        char *hostheader= /* host:port with IPv6 support */
-          aprintf("%s%s%s:%hu", conn->bits.ipv6_ip?"[":"",
-                  hostname, conn->bits.ipv6_ip?"]":"",
+        bool ipv6_ip = conn->bits.ipv6_ip;
+        char *hostheader;
+
+        /* the hostname may be different */
+        if(hostname != conn->host.name)
+          ipv6_ip = (strchr(hostname, ':') != NULL);
+        hostheader= /* host:port with IPv6 support */
+          aprintf("%s%s%s:%hu", ipv6_ip?"[":"", hostname, ipv6_ip?"]":"",
                   remote_port);
         if(!hostheader) {
           Curl_add_buffer_free(req_buffer);
@@ -171,9 +185,6 @@ CURLcode Curl_proxyCONNECT(struct connectdata *conn,
             return CURLE_OUT_OF_MEMORY;
           }
         }
-        if(!Curl_checkProxyheaders(conn, "Proxy-Connection:"))
-          proxyconn = "Proxy-Connection: Keep-Alive\r\n";
-
         if(!Curl_checkProxyheaders(conn, "User-Agent:") &&
            data->set.str[STRING_USERAGENT])
           useragent = conn->allocptr.uagent;
@@ -183,15 +194,13 @@ CURLcode Curl_proxyCONNECT(struct connectdata *conn,
                            "CONNECT %s HTTP/%s\r\n"
                            "%s"  /* Host: */
                            "%s"  /* Proxy-Authorization */
-                           "%s"  /* User-Agent */
-                           "%s", /* Proxy-Connection */
+                           "%s", /* User-Agent */
                            hostheader,
                            http,
                            host,
                            conn->allocptr.proxyuserpwd?
                            conn->allocptr.proxyuserpwd:"",
-                           useragent,
-                           proxyconn);
+                           useragent);
 
         if(host && *host)
           free(host);