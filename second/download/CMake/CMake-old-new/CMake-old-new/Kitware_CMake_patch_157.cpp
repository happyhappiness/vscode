@@ -5,12 +5,12 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 2012, Linus Nielsen Feltzing, <linus@haxx.se>
+ * Copyright (C) 2012, 2016, Linus Nielsen Feltzing, <linus@haxx.se>
  * Copyright (C) 2012 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
- * are also available at http://curl.haxx.se/docs/copyright.html.
+ * are also available at https://curl.haxx.se/docs/copyright.html.
  *
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
@@ -32,10 +32,9 @@
 #include "sendf.h"
 #include "rawstr.h"
 #include "conncache.h"
+/* The last 3 #include files should be in this order */
 #include "curl_printf.h"
-
 #include "curl_memory.h"
-/* The last #include file should be: */
 #include "memdebug.h"
 
 static void conn_llist_dtor(void *user, void *element)
@@ -46,7 +45,7 @@ static void conn_llist_dtor(void *user, void *element)
   data->bundle = NULL;
 }
 
-static CURLcode bundle_create(struct SessionHandle *data,
+static CURLcode bundle_create(struct Curl_easy *data,
                               struct connectbundle **cb_ptr)
 {
   (void)data;
@@ -132,9 +131,16 @@ void Curl_conncache_destroy(struct conncache *connc)
 /* returns an allocated key to find a bundle for this connection */
 static char *hashkey(struct connectdata *conn)
 {
-  return aprintf("%s:%d",
-                 conn->bits.proxy?conn->proxy.name:conn->host.name,
-                 conn->localport);
+  const char *hostname;
+
+  if(conn->bits.proxy)
+    hostname = conn->proxy.name;
+  else if(conn->bits.conn_to_host)
+    hostname = conn->conn_to_host.name;
+  else
+    hostname = conn->host.name;
+
+  return aprintf("%s:%d", hostname, conn->port);
 }
 
 /* Look up the bundle with all the connections to the same host this
@@ -193,7 +199,7 @@ CURLcode Curl_conncache_add_conn(struct conncache *connc,
   CURLcode result;
   struct connectbundle *bundle;
   struct connectbundle *new_bundle = NULL;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
 
   bundle = Curl_conncache_find_bundle(conn, data->state.conn_cache);
   if(!bundle) {