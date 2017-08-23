@@ -5,8 +5,8 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 2012, 2016, Linus Nielsen Feltzing, <linus@haxx.se>
- * Copyright (C) 2012 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 2012 - 2016, Linus Nielsen Feltzing, <linus@haxx.se>
+ * Copyright (C) 2012 - 2017, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -56,11 +56,7 @@ static CURLcode bundle_create(struct Curl_easy *data,
   (*cb_ptr)->num_connections = 0;
   (*cb_ptr)->multiuse = BUNDLE_UNKNOWN;
 
-  (*cb_ptr)->conn_list = Curl_llist_alloc((curl_llist_dtor) conn_llist_dtor);
-  if(!(*cb_ptr)->conn_list) {
-    Curl_safefree(*cb_ptr);
-    return CURLE_OUT_OF_MEMORY;
-  }
+  Curl_llist_init(&(*cb_ptr)->conn_list, (curl_llist_dtor) conn_llist_dtor);
   return CURLE_OK;
 }
 
@@ -69,18 +65,16 @@ static void bundle_destroy(struct connectbundle *cb_ptr)
   if(!cb_ptr)
     return;
 
-  if(cb_ptr->conn_list) {
-    Curl_llist_destroy(cb_ptr->conn_list, NULL);
-    cb_ptr->conn_list = NULL;
-  }
+  Curl_llist_destroy(&cb_ptr->conn_list, NULL);
+
   free(cb_ptr);
 }
 
 /* Add a connection to a bundle */
 static CURLcode bundle_add_conn(struct connectbundle *cb_ptr,
                               struct connectdata *conn)
 {
-  if(!Curl_llist_insert_next(cb_ptr->conn_list, cb_ptr->conn_list->tail, conn))
+  if(!Curl_llist_insert_next(&cb_ptr->conn_list, cb_ptr->conn_list.tail, conn))
     return CURLE_OUT_OF_MEMORY;
 
   conn->bundle = cb_ptr;
@@ -95,10 +89,10 @@ static int bundle_remove_conn(struct connectbundle *cb_ptr,
 {
   struct curl_llist_element *curr;
 
-  curr = cb_ptr->conn_list->head;
+  curr = cb_ptr->conn_list.head;
   while(curr) {
     if(curr->ptr == conn) {
-      Curl_llist_remove(cb_ptr->conn_list, curr, NULL);
+      Curl_llist_remove(&cb_ptr->conn_list, curr, NULL);
       cb_ptr->num_connections--;
       conn->bundle = NULL;
       return 1; /* we removed a handle */
@@ -127,8 +121,9 @@ void Curl_conncache_destroy(struct conncache *connc)
     Curl_hash_destroy(&connc->hash);
 }
 
-/* returns an allocated key to find a bundle for this connection */
-static char *hashkey(struct connectdata *conn)
+/* creates a key to find a bundle for this connection */
+static void hashkey(struct connectdata *conn, char *buf,
+                    size_t len) /* something like 128 is fine */
 {
   const char *hostname;
 
@@ -141,7 +136,10 @@ static char *hashkey(struct connectdata *conn)
   else
     hostname = conn->host.name;
 
-  return aprintf("%s:%d", hostname, conn->port);
+  DEBUGASSERT(len > 32);
+
+  /* put the number first so that the hostname gets cut off if too long */
+  snprintf(buf, len, "%ld%s", conn->port, hostname);
 }
 
 /* Look up the bundle with all the connections to the same host this
@@ -151,11 +149,9 @@ struct connectbundle *Curl_conncache_find_bundle(struct connectdata *conn,
 {
   struct connectbundle *bundle = NULL;
   if(connc) {
-    char *key = hashkey(conn);
-    if(key) {
-      bundle = Curl_hash_pick(&connc->hash, key, strlen(key));
-      free(key);
-    }
+    char key[128];
+    hashkey(conn, key, sizeof(key));
+    bundle = Curl_hash_pick(&connc->hash, key, strlen(key));
   }
 
   return bundle;
@@ -204,21 +200,16 @@ CURLcode Curl_conncache_add_conn(struct conncache *connc,
 
   bundle = Curl_conncache_find_bundle(conn, data->state.conn_cache);
   if(!bundle) {
-    char *key;
     int rc;
+    char key[128];
 
     result = bundle_create(data, &new_bundle);
     if(result)
       return result;
 
-    key = hashkey(conn);
-    if(!key) {
-      bundle_destroy(new_bundle);
-      return CURLE_OUT_OF_MEMORY;
-    }
-
+    hashkey(conn, key, sizeof(key));
     rc = conncache_add_bundle(data->state.conn_cache, key, new_bundle);
-    free(key);
+
     if(!rc) {
       bundle_destroy(new_bundle);
       return CURLE_OUT_OF_MEMORY;
@@ -292,7 +283,7 @@ void Curl_conncache_foreach(struct conncache *connc,
     bundle = he->ptr;
     he = Curl_hash_next_element(&iter);
 
-    curr = bundle->conn_list->head;
+    curr = bundle->conn_list.head;
     while(curr) {
       /* Yes, we need to update curr before calling func(), because func()
          might decide to remove the connection */
@@ -321,7 +312,7 @@ Curl_conncache_find_first_connection(struct conncache *connc)
     struct curl_llist_element *curr;
     bundle = he->ptr;
 
-    curr = bundle->conn_list->head;
+    curr = bundle->conn_list.head;
     if(curr) {
       return curr->ptr;
     }