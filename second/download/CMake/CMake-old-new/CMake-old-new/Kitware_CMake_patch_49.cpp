@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2017, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -411,10 +411,7 @@ CURLcode Curl_close(struct Curl_easy *data)
   /* Destroy the timeout list that is held in the easy handle. It is
      /normally/ done by curl_multi_remove_handle() but this is "just in
      case" */
-  if(data->state.timeoutlist) {
-    Curl_llist_destroy(data->state.timeoutlist, NULL);
-    data->state.timeoutlist = NULL;
-  }
+  Curl_llist_destroy(&data->state.timeoutlist, NULL);
 
   data->magic = 0; /* force a clear AFTER the possibly enforced removal from
                       the multi handle, since that function uses the magic
@@ -452,6 +449,7 @@ CURLcode Curl_close(struct Curl_easy *data)
   }
   data->change.url = NULL;
 
+  Curl_safefree(data->state.buffer);
   Curl_safefree(data->state.headerbuff);
 
   Curl_flush_cookies(data, 1);
@@ -548,7 +546,7 @@ CURLcode Curl_init_userdefined(struct UserDefined *set)
 #endif
   set->ssh_auth_types = CURLSSH_AUTH_DEFAULT; /* defaults to any auth
                                                       type */
-  set->general_ssl.sessionid = TRUE; /* session ID caching enabled by
+  set->ssl.primary.sessionid = TRUE; /* session ID caching enabled by
                                         default */
   set->proxy_ssl = set->ssl;
 
@@ -576,14 +574,19 @@ CURLcode Curl_init_userdefined(struct UserDefined *set)
   result = setstropt(&set->str[STRING_SSL_CAFILE_ORIG], CURL_CA_BUNDLE);
   if(result)
     return result;
+
+  result = setstropt(&set->str[STRING_SSL_CAFILE_PROXY], CURL_CA_BUNDLE);
+  if(result)
+    return result;
 #endif
 #if defined(CURL_CA_PATH)
   result = setstropt(&set->str[STRING_SSL_CAPATH_ORIG], CURL_CA_PATH);
   if(result)
     return result;
 
-  result = setstropt(&set->str[STRING_SSL_CAPATH_PROXY],
-                     (char *) CURL_CA_PATH);
+  result = setstropt(&set->str[STRING_SSL_CAPATH_PROXY], CURL_CA_PATH);
+  if(result)
+    return result;
 #endif
 
   set->wildcardmatch  = FALSE;
@@ -641,6 +644,12 @@ CURLcode Curl_open(struct Curl_easy **curl)
 
   /* We do some initial setup here, all those fields that can't be just 0 */
 
+  data->state.buffer = malloc(BUFSIZE + 1);
+  if(!data->state.buffer) {
+    DEBUGF(fprintf(stderr, "Error: malloc of buffer failed\n"));
+    result = CURLE_OUT_OF_MEMORY;
+  }
+
   data->state.headerbuff = malloc(HEADERSIZE);
   if(!data->state.headerbuff) {
     DEBUGF(fprintf(stderr, "Error: malloc of headerbuff failed\n"));
@@ -660,9 +669,6 @@ CURLcode Curl_open(struct Curl_easy **curl)
 
     data->progress.flags |= PGRS_HIDE;
     data->state.current_speed = -1; /* init to negative == impossible */
-
-    data->wildcard.state = CURLWC_INIT;
-    data->wildcard.filelist = NULL;
     data->set.fnmatch = ZERO_NULL;
     data->set.maxconnects = DEFAULT_CONNCACHE_SIZE; /* for easy handles */
 
@@ -671,6 +677,7 @@ CURLcode Curl_open(struct Curl_easy **curl)
 
   if(result) {
     Curl_resolver_cleanup(data->state.resolver);
+    free(data->state.buffer);
     free(data->state.headerbuff);
     Curl_freeset(data);
     free(data);
@@ -682,6 +689,9 @@ CURLcode Curl_open(struct Curl_easy **curl)
   return result;
 }
 
+#define C_SSLVERSION_VALUE(x) (x & 0xffff)
+#define C_SSLVERSION_MAX_VALUE(x) (x & 0xffff0000)
+
 CURLcode Curl_setopt(struct Curl_easy *data, CURLoption option,
                      va_list param)
 {
@@ -914,7 +924,9 @@ CURLcode Curl_setopt(struct Curl_easy *data, CURLoption option,
      * implementations are lame.
      */
 #ifdef USE_SSL
-    data->set.ssl.primary.version = va_arg(param, long);
+    arg = va_arg(param, long);
+    data->set.ssl.primary.version = C_SSLVERSION_VALUE(arg);
+    data->set.ssl.primary.version_max = C_SSLVERSION_MAX_VALUE(arg);
 #else
     result = CURLE_UNKNOWN_OPTION;
 #endif
@@ -925,7 +937,9 @@ CURLcode Curl_setopt(struct Curl_easy *data, CURLoption option,
      * implementations are lame.
      */
 #ifdef USE_SSL
-    data->set.proxy_ssl.primary.version = va_arg(param, long);
+    arg = va_arg(param, long);
+    data->set.proxy_ssl.primary.version = C_SSLVERSION_VALUE(arg);
+    data->set.proxy_ssl.primary.version_max = C_SSLVERSION_MAX_VALUE(arg);
 #else
     result = CURLE_UNKNOWN_OPTION;
 #endif
@@ -2217,8 +2231,12 @@ CURLcode Curl_setopt(struct Curl_easy *data, CURLoption option,
     /* This does not work on windows. */
     result = setstropt(&data->set.str[STRING_SSL_CAPATH_ORIG],
                        va_arg(param, char *));
+#else
+    result = CURLE_NOT_BUILT_IN;
+#endif
     break;
   case CURLOPT_PROXY_CAPATH:
+#ifdef have_curlssl_ca_path /* not supported by all backends */
     /*
      * Set CA path info for SSL connection proxy. Specify directory name of the
      * CA certificates which have been prepared using openssl c_rehash utility.
@@ -2268,9 +2286,20 @@ CURLcode Curl_setopt(struct Curl_easy *data, CURLoption option,
      */
     data->set.buffer_size = va_arg(param, long);
 
-    if((data->set.buffer_size> (BUFSIZE -1)) ||
-       (data->set.buffer_size < 1))
-      data->set.buffer_size = 0; /* huge internal default */
+    if(data->set.buffer_size > MAX_BUFSIZE)
+      data->set.buffer_size = MAX_BUFSIZE; /* huge internal default */
+    else if(data->set.buffer_size < 1)
+      data->set.buffer_size = BUFSIZE;
+
+    /* Resize only if larger than default buffer size. */
+    if(data->set.buffer_size > BUFSIZE) {
+      data->state.buffer = realloc(data->state.buffer,
+                                   data->set.buffer_size + 1);
+      if(!data->state.buffer) {
+        DEBUGF(fprintf(stderr, "Error: realloc of buffer failed\n"));
+        result = CURLE_OUT_OF_MEMORY;
+      }
+    }
 
     break;
 
@@ -2470,8 +2499,9 @@ CURLcode Curl_setopt(struct Curl_easy *data, CURLoption option,
     break;
 
   case CURLOPT_SSL_SESSIONID_CACHE:
-    data->set.general_ssl.sessionid = (0 != va_arg(param, long)) ?
+    data->set.ssl.primary.sessionid = (0 != va_arg(param, long)) ?
                                       TRUE : FALSE;
+    data->set.proxy_ssl.primary.sessionid = data->set.ssl.primary.sessionid;
     break;
 
 #ifdef USE_LIBSSH2
@@ -2814,6 +2844,12 @@ CURLcode Curl_setopt(struct Curl_easy *data, CURLoption option,
 
 #ifdef USE_UNIX_SOCKETS
   case CURLOPT_UNIX_SOCKET_PATH:
+    data->set.abstract_unix_socket = FALSE;
+    result = setstropt(&data->set.str[STRING_UNIX_SOCKET_PATH],
+                       va_arg(param, char *));
+    break;
+  case CURLOPT_ABSTRACT_UNIX_SOCKET:
+    data->set.abstract_unix_socket = TRUE;
     result = setstropt(&data->set.str[STRING_UNIX_SOCKET_PATH],
                        va_arg(param, char *));
     break;
@@ -2853,6 +2889,9 @@ CURLcode Curl_setopt(struct Curl_easy *data, CURLoption option,
   case CURLOPT_CONNECT_TO:
     data->set.connect_to = va_arg(param, struct curl_slist *);
     break;
+  case CURLOPT_SUPPRESS_CONNECT_HEADERS:
+    data->set.suppress_connect_headers = (0 != va_arg(param, long))?TRUE:FALSE;
+    break;
   default:
     /* unknown tag and its companion, just ignore: */
     result = CURLE_UNKNOWN_OPTION;
@@ -2957,11 +2996,8 @@ static void conn_free(struct connectdata *conn)
 
   conn_reset_all_postponed_data(conn);
 
-  Curl_llist_destroy(conn->send_pipe, NULL);
-  Curl_llist_destroy(conn->recv_pipe, NULL);
-
-  conn->send_pipe = NULL;
-  conn->recv_pipe = NULL;
+  Curl_llist_destroy(&conn->send_pipe, NULL);
+  Curl_llist_destroy(&conn->recv_pipe, NULL);
 
   Curl_safefree(conn->localdev);
   Curl_free_primary_ssl_config(&conn->ssl_config);
@@ -3001,9 +3037,9 @@ CURLcode Curl_disconnect(struct connectdata *conn, bool dead_connection)
    * are other users of it
    */
   if(!conn->bits.close &&
-     (conn->send_pipe->size + conn->recv_pipe->size)) {
+     (conn->send_pipe.size + conn->recv_pipe.size)) {
     DEBUGF(infof(data, "Curl_disconnect, usecounter: %d\n",
-                 conn->send_pipe->size + conn->recv_pipe->size));
+                 conn->send_pipe.size + conn->recv_pipe.size));
     return CURLE_OK;
   }
 
@@ -3029,16 +3065,15 @@ CURLcode Curl_disconnect(struct connectdata *conn, bool dead_connection)
 
   free_fixed_hostname(&conn->host);
   free_fixed_hostname(&conn->conn_to_host);
-  free_fixed_hostname(&conn->proxy);
   free_fixed_hostname(&conn->http_proxy.host);
   free_fixed_hostname(&conn->socks_proxy.host);
 
   Curl_ssl_close(conn, FIRSTSOCKET);
 
   /* Indicate to all handles on the pipe that we're dead */
   if(Curl_pipeline_wanted(data->multi, CURLPIPE_ANY)) {
-    signalPipeClose(conn->send_pipe, TRUE);
-    signalPipeClose(conn->recv_pipe, TRUE);
+    signalPipeClose(&conn->send_pipe, TRUE);
+    signalPipeClose(&conn->recv_pipe, TRUE);
   }
 
   conn_free(conn);
@@ -3143,9 +3178,9 @@ void Curl_getoff_all_pipelines(struct Curl_easy *data,
   bool send_head = (conn->writechannel_inuse &&
                     Curl_sendpipe_head(data, conn));
 
-  if(Curl_removeHandleFromPipeline(data, conn->recv_pipe) && recv_head)
+  if(Curl_removeHandleFromPipeline(data, &conn->recv_pipe) && recv_head)
     Curl_pipeline_leave_read(conn);
-  if(Curl_removeHandleFromPipeline(data, conn->send_pipe) && send_head)
+  if(Curl_removeHandleFromPipeline(data, &conn->send_pipe) && send_head)
     Curl_pipeline_leave_write(conn);
 }
 
@@ -3206,7 +3241,7 @@ Curl_oldest_idle_connection(struct Curl_easy *data)
 
     bundle = he->ptr;
 
-    curr = bundle->conn_list->head;
+    curr = bundle->conn_list.head;
     while(curr) {
       conn = curr->ptr;
 
@@ -3234,9 +3269,7 @@ proxy_info_matches(const struct proxy_info* data,
 {
   if((data->proxytype == needle->proxytype) &&
      (data->port == needle->port) &&
-     Curl_safe_strcasecompare(data->host.name, needle->host.name) &&
-     Curl_safe_strcasecompare(data->user, needle->user) &&
-     Curl_safe_strcasecompare(data->passwd, needle->passwd))
+     Curl_safe_strcasecompare(data->host.name, needle->host.name))
     return TRUE;
 
   return FALSE;
@@ -3265,7 +3298,7 @@ find_oldest_idle_connection_in_bundle(struct Curl_easy *data,
 
   now = Curl_tvnow();
 
-  curr = bundle->conn_list->head;
+  curr = bundle->conn_list.head;
   while(curr) {
     conn = curr->ptr;
 
@@ -3293,7 +3326,7 @@ find_oldest_idle_connection_in_bundle(struct Curl_easy *data,
 static bool disconnect_if_dead(struct connectdata *conn,
                                struct Curl_easy *data)
 {
-  size_t pipeLen = conn->send_pipe->size + conn->recv_pipe->size;
+  size_t pipeLen = conn->send_pipe.size + conn->recv_pipe.size;
   if(!pipeLen && !conn->inuse) {
     /* The check for a dead socket makes sense only if there are no
        handles in pipeline and the connection isn't already marked in
@@ -3406,19 +3439,14 @@ ConnectionExists(struct Curl_easy *data,
       max_pipeline_length(data->multi):0;
     size_t best_pipe_len = max_pipe_len;
     struct curl_llist_element *curr;
-    const char *hostname;
-
-    if(needle->bits.conn_to_host)
-      hostname = needle->conn_to_host.name;
-    else
-      hostname = needle->host.name;
 
     infof(data, "Found bundle for host %s: %p [%s]\n",
-          hostname, (void *)bundle,
-          (bundle->multiuse== BUNDLE_PIPELINING?
-           "can pipeline":
-           (bundle->multiuse== BUNDLE_MULTIPLEX?
-            "can multiplex":"serially")));
+          (needle->bits.conn_to_host ? needle->conn_to_host.name :
+           needle->host.name), (void *)bundle,
+          (bundle->multiuse == BUNDLE_PIPELINING ?
+           "can pipeline" :
+           (bundle->multiuse == BUNDLE_MULTIPLEX ?
+            "can multiplex" : "serially")));
 
     /* We can't pipe if we don't know anything about the server */
     if(canPipeline) {
@@ -3445,7 +3473,7 @@ ConnectionExists(struct Curl_easy *data,
       }
     }
 
-    curr = bundle->conn_list->head;
+    curr = bundle->conn_list.head;
     while(curr) {
       bool match = FALSE;
       size_t pipeLen;
@@ -3460,16 +3488,16 @@ ConnectionExists(struct Curl_easy *data,
       if(disconnect_if_dead(check, data))
         continue;
 
-      pipeLen = check->send_pipe->size + check->recv_pipe->size;
+      pipeLen = check->send_pipe.size + check->recv_pipe.size;
 
       if(canPipeline) {
         if(check->bits.protoconnstart && check->bits.close)
           continue;
 
         if(!check->bits.multiplex) {
           /* If not multiplexing, make sure the pipe has only GET requests */
-          struct Curl_easy* sh = gethandleathead(check->send_pipe);
-          struct Curl_easy* rh = gethandleathead(check->recv_pipe);
+          struct Curl_easy* sh = gethandleathead(&check->send_pipe);
+          struct Curl_easy* rh = gethandleathead(&check->recv_pipe);
           if(sh) {
             if(!IsPipeliningPossible(sh, check))
               continue;
@@ -3507,7 +3535,7 @@ ConnectionExists(struct Curl_easy *data,
           infof(data, "Connection #%ld isn't open enough, can't reuse\n",
                 check->connection_id);
 #ifdef DEBUGBUILD
-          if(check->recv_pipe->size > 0) {
+          if(check->recv_pipe.size > 0) {
             infof(data,
                   "BAD! Unconnected #%ld has a non-empty recv pipeline!\n",
                   check->connection_id);
@@ -3523,6 +3551,8 @@ ConnectionExists(struct Curl_easy *data,
           continue;
         if(strcmp(needle->unix_domain_socket, check->unix_domain_socket))
           continue;
+        if(needle->abstract_unix_socket != check->abstract_unix_socket)
+          continue;
       }
       else if(check->unix_domain_socket)
         continue;
@@ -3644,7 +3674,7 @@ ConnectionExists(struct Curl_easy *data,
                            check->connection_id));
               continue;
             }
-            else if(check->ssl[FIRSTSOCKET].state != ssl_connection_complete) {
+            if(check->ssl[FIRSTSOCKET].state != ssl_connection_complete) {
               foundPendingCandidate = TRUE;
               DEBUGF(infof(data,
                            "Connection #%ld has not started SSL connect, "
@@ -3797,17 +3827,19 @@ CURLcode Curl_connected_proxy(struct connectdata *conn, int sockindex)
 
   if(conn->bits.socksproxy) {
 #ifndef CURL_DISABLE_PROXY
-    const char * const host = conn->bits.conn_to_host ?
-                              conn->conn_to_host.name :
-                              conn->bits.httpproxy ?
+    /* for the secondary socket (FTP), use the "connect to host"
+     * but ignore the "connect to port" (use the secondary port)
+     */
+    const char * const host = conn->bits.httpproxy ?
                               conn->http_proxy.host.name :
+                              conn->bits.conn_to_host ?
+                              conn->conn_to_host.name :
                               sockindex == SECONDARYSOCKET ?
                               conn->secondaryhostname : conn->host.name;
-    const int port = conn->bits.conn_to_port ? conn->conn_to_port :
-                     conn->bits.httpproxy ?
-                     (int)conn->http_proxy.port :
-                     sockindex == SECONDARYSOCKET ?
-                      conn->secondary_port : conn->remote_port;
+    const int port = conn->bits.httpproxy ? (int)conn->http_proxy.port :
+                     sockindex == SECONDARYSOCKET ? conn->secondary_port :
+                     conn->bits.conn_to_port ? conn->conn_to_port :
+                     conn->remote_port;
     conn->bits.socksproxy_connecting = TRUE;
     switch(conn->socks_proxy.proxytype) {
     case CURLPROXY_SOCKS5:
@@ -3845,7 +3877,8 @@ void Curl_verboseconnect(struct connectdata *conn)
     infof(conn->data, "Connected to %s (%s) port %ld (#%ld)\n",
           conn->bits.socksproxy ? conn->socks_proxy.host.dispname :
           conn->bits.httpproxy ? conn->http_proxy.host.dispname :
-                             conn->host.dispname,
+          conn->bits.conn_to_host ? conn->conn_to_host.dispname :
+          conn->host.dispname,
           conn->ip_addr_str, conn->port, conn->connection_id);
 }
 #endif
@@ -3968,7 +4001,7 @@ CURLcode Curl_protocol_connect(struct connectdata *conn,
 }
 
 /*
- * Helpers for IDNA convertions.
+ * Helpers for IDNA conversions.
  */
 static bool is_ASCII_name(const char *hostname)
 {
@@ -4010,7 +4043,15 @@ static void fix_hostname(struct connectdata *conn, struct hostname *host)
 #ifdef USE_LIBIDN2
     if(idn2_check_version(IDN2_VERSION)) {
       char *ace_hostname = NULL;
-      int rc = idn2_lookup_ul((const char *)host->name, &ace_hostname, 0);
+#if IDN2_VERSION_NUMBER >= 0x00140000
+      /* IDN2_NFC_INPUT: Normalize input string using normalization form C.
+         IDN2_NONTRANSITIONAL: Perform Unicode TR46 non-transitional
+         processing. */
+      int flags = IDN2_NFC_INPUT | IDN2_NONTRANSITIONAL;
+#else
+      int flags = IDN2_NFC_INPUT;
+#endif
+      int rc = idn2_lookup_ul((const char *)host->name, &ace_hostname, flags);
       if(rc == IDN2_OK) {
         host->encalloc = (char *)ace_hostname;
         /* change the name pointer to point to the encoded hostname */
@@ -4084,7 +4125,7 @@ static struct connectdata *allocate_conn(struct Curl_easy *data)
   conn->tempsock[1] = CURL_SOCKET_BAD; /* no file descriptor */
   conn->connection_id = -1;    /* no ID */
   conn->port = -1; /* unknown at this point */
-  conn->remote_port = -1; /* unknown */
+  conn->remote_port = -1; /* unknown at this point */
 #if defined(USE_RECV_BEFORE_SEND_WORKAROUND) && defined(DEBUGBUILD)
   conn->postponed[0].bindsock = CURL_SOCKET_BAD; /* no file descriptor */
   conn->postponed[1].bindsock = CURL_SOCKET_BAD; /* no file descriptor */
@@ -4141,8 +4182,11 @@ static struct connectdata *allocate_conn(struct Curl_easy *data)
   conn->bits.ftp_use_epsv = data->set.ftp_use_epsv;
   conn->bits.ftp_use_eprt = data->set.ftp_use_eprt;
 
+  conn->ssl_config.verifystatus = data->set.ssl.primary.verifystatus;
   conn->ssl_config.verifypeer = data->set.ssl.primary.verifypeer;
   conn->ssl_config.verifyhost = data->set.ssl.primary.verifyhost;
+  conn->proxy_ssl_config.verifystatus =
+    data->set.proxy_ssl.primary.verifystatus;
   conn->proxy_ssl_config.verifypeer = data->set.proxy_ssl.primary.verifypeer;
   conn->proxy_ssl_config.verifyhost = data->set.proxy_ssl.primary.verifyhost;
 
@@ -4165,10 +4209,8 @@ static struct connectdata *allocate_conn(struct Curl_easy *data)
   }
 
   /* Initialize the pipeline lists */
-  conn->send_pipe = Curl_llist_alloc((curl_llist_dtor) llist_dtor);
-  conn->recv_pipe = Curl_llist_alloc((curl_llist_dtor) llist_dtor);
-  if(!conn->send_pipe || !conn->recv_pipe)
-    goto error;
+  Curl_llist_init(&conn->send_pipe, (curl_llist_dtor) llist_dtor);
+  Curl_llist_init(&conn->recv_pipe, (curl_llist_dtor) llist_dtor);
 
 #ifdef HAVE_GSSAPI
   conn->data_prot = PROT_CLEAR;
@@ -4191,11 +4233,8 @@ static struct connectdata *allocate_conn(struct Curl_easy *data)
   return conn;
   error:
 
-  Curl_llist_destroy(conn->send_pipe, NULL);
-  Curl_llist_destroy(conn->recv_pipe, NULL);
-
-  conn->send_pipe = NULL;
-  conn->recv_pipe = NULL;
+  Curl_llist_destroy(&conn->send_pipe, NULL);
+  Curl_llist_destroy(&conn->recv_pipe, NULL);
 
   free(conn->master_buffer);
   free(conn->localdev);
@@ -4258,11 +4297,13 @@ static CURLcode parseurlandfillconn(struct Curl_easy *data,
   char *fragment;
   char *path = data->state.path;
   char *query;
+  int i;
   int rc;
-  char protobuf[16] = "";
   const char *protop = "";
   CURLcode result;
   bool rebuild_url = FALSE;
+  bool url_has_scheme = FALSE;
+  char protobuf[16];
 
   *prot_missing = FALSE;
 
@@ -4281,10 +4322,47 @@ static CURLcode parseurlandfillconn(struct Curl_easy *data,
    * proxy -- and we don't know if we will need to use SSL until we parse the
    * url ...
    ************************************************************/
-  if((2 == sscanf(data->change.url, "%15[^:]:%[^\n]",
-                  protobuf, path)) &&
-     strcasecompare(protobuf, "file")) {
-    if(path[0] == '/' && path[1] == '/') {
+  if(data->change.url[0] == ':') {
+    failf(data, "Bad URL, colon is first character");
+    return CURLE_URL_MALFORMAT;
+  }
+
+  /* Make sure we don't mistake a drive letter for a scheme, for example:
+     curld --proto-default file c:/foo/bar.txt */
+  if((('a' <= data->change.url[0] && data->change.url[0] <= 'z') ||
+      ('A' <= data->change.url[0] && data->change.url[0] <= 'Z')) &&
+     data->change.url[1] == ':' && data->set.str[STRING_DEFAULT_PROTOCOL] &&
+     strcasecompare(data->set.str[STRING_DEFAULT_PROTOCOL], "file")) {
+    ; /* do nothing */
+  }
+  else { /* check for a scheme */
+    for(i = 0; i < 16 && data->change.url[i]; ++i) {
+      if(data->change.url[i] == '/')
+        break;
+      if(data->change.url[i] == ':') {
+        url_has_scheme = TRUE;
+        break;
+      }
+    }
+  }
+
+  /* handle the file: scheme */
+  if((url_has_scheme && strncasecompare(data->change.url, "file:", 5)) ||
+     (!url_has_scheme && data->set.str[STRING_DEFAULT_PROTOCOL] &&
+      strcasecompare(data->set.str[STRING_DEFAULT_PROTOCOL], "file"))) {
+    bool path_has_drive = FALSE;
+
+    if(url_has_scheme)
+      rc = sscanf(data->change.url, "%*15[^\n/:]:%[^\n]", path);
+    else
+      rc = sscanf(data->change.url, "%[^\n]", path);
+
+    if(rc != 1) {
+      failf(data, "Bad URL");
+      return CURLE_URL_MALFORMAT;
+    }
+
+    if(url_has_scheme && path[0] == '/' && path[1] == '/') {
       /* Allow omitted hostname (e.g. file:/<path>).  This is not strictly
        * speaking a valid file: URL by RFC 1738, but treating file:/<path> as
        * file://localhost/<path> is similar to how other schemes treat missing
@@ -4294,18 +4372,25 @@ static CURLcode parseurlandfillconn(struct Curl_easy *data,
          memory areas overlap! */
       memmove(path, path + 2, strlen(path + 2)+1);
     }
+
+    /* the path may start with a drive letter. for backwards compatibility
+       we skip some processing on those paths. */
+    path_has_drive = (('a' <= path[0] && path[0] <= 'z') ||
+                      ('A' <= path[0] && path[0] <= 'Z')) && path[1] == ':';
+
     /*
      * we deal with file://<host>/<path> differently since it supports no
      * hostname other than "localhost" and "127.0.0.1", which is unique among
      * the URL protocols specified in RFC 1738
      */
-    if(path[0] != '/') {
+    if(path[0] != '/' && !path_has_drive) {
       /* the URL includes a host name, it must match "localhost" or
          "127.0.0.1" to be valid */
       char *ptr;
       if(!checkprefix("localhost/", path) &&
          !checkprefix("127.0.0.1/", path)) {
-        failf(data, "Valid host name with slash missing in URL");
+        failf(data, "Invalid file://hostname/, "
+                    "expected localhost or 127.0.0.1 or none");
         return CURLE_URL_MALFORMAT;
       }
       ptr = &path[9]; /* now points to the slash after the host */
@@ -4332,7 +4417,17 @@ static CURLcode parseurlandfillconn(struct Curl_easy *data,
 
       /* This cannot be made with strcpy, as the memory chunks overlap! */
       memmove(path, ptr, strlen(ptr)+1);
+
+      path_has_drive = (('a' <= path[0] && path[0] <= 'z') ||
+                        ('A' <= path[0] && path[0] <= 'Z')) && path[1] == ':';
+    }
+
+#if !defined(MSDOS) && !defined(WIN32) && !defined(__CYGWIN__)
+    if(path_has_drive) {
+      failf(data, "File drive letters are only accepted in MSDOS/Windows.");
+      return CURLE_URL_MALFORMAT;
     }
+#endif
 
     protop = "file"; /* protocol string */
   }
@@ -4342,7 +4437,7 @@ static CURLcode parseurlandfillconn(struct Curl_easy *data,
     path[0]=0;
 
     rc = sscanf(data->change.url,
-                "%15[^\n:]:%3[/]%[^\n/?#]%[^\n]",
+                "%15[^\n/:]:%3[/]%[^\n/?#]%[^\n]",
                 protobuf, slashbuf, conn->host.name, path);
     if(2 == rc) {
       failf(data, "Bad URL");
@@ -4527,6 +4622,10 @@ static CURLcode parseurlandfillconn(struct Curl_easy *data,
     data->change.url_alloc = TRUE; /* free this later */
   }
 
+  result = findprotocol(data, conn, protop);
+  if(result)
+    return result;
+
   /*
    * Parse the login details from the URL and strip them out of
    * the host name
@@ -4613,8 +4712,7 @@ static CURLcode parseurlandfillconn(struct Curl_easy *data,
    *   conn->host.name is B
    *   data->state.path is /C
    */
-
-  return findprotocol(data, conn, protop);
+  return CURLE_OK;
 }
 
 /*
@@ -4783,6 +4881,7 @@ static bool check_noproxy(const char *name, const char *no_proxy)
   return FALSE;
 }
 
+#ifndef CURL_DISABLE_HTTP
 /****************************************************************
 * Detect what (if any) proxy to use. Remember that this selects a host
 * name and is not limited to HTTP proxies only.
@@ -4792,7 +4891,6 @@ static char *detect_proxy(struct connectdata *conn)
 {
   char *proxy = NULL;
 
-#ifndef CURL_DISABLE_HTTP
   /* If proxy was not specified, we check for default proxy environment
    * variables, to enable i.e Lynx compliance:
    *
@@ -4810,65 +4908,50 @@ static char *detect_proxy(struct connectdata *conn)
    * For compatibility, the all-uppercase versions of these variables are
    * checked if the lowercase versions don't exist.
    */
-  char *no_proxy=NULL;
   char proxy_env[128];
+  const char *protop = conn->handler->scheme;
+  char *envp = proxy_env;
+  char *prox;
 
-  no_proxy=curl_getenv("no_proxy");
-  if(!no_proxy)
-    no_proxy=curl_getenv("NO_PROXY");
-
-  if(!check_noproxy(conn->host.name, no_proxy)) {
-    /* It was not listed as without proxy */
-    const char *protop = conn->handler->scheme;
-    char *envp = proxy_env;
-    char *prox;
+  /* Now, build <protocol>_proxy and check for such a one to use */
+  while(*protop)
+    *envp++ = (char)tolower((int)*protop++);
 
-    /* Now, build <protocol>_proxy and check for such a one to use */
-    while(*protop)
-      *envp++ = (char)tolower((int)*protop++);
+  /* append _proxy */
+  strcpy(envp, "_proxy");
 
-    /* append _proxy */
-    strcpy(envp, "_proxy");
+  /* read the protocol proxy: */
+  prox=curl_getenv(proxy_env);
 
-    /* read the protocol proxy: */
+  /*
+   * We don't try the uppercase version of HTTP_PROXY because of
+   * security reasons:
+   *
+   * When curl is used in a webserver application
+   * environment (cgi or php), this environment variable can
+   * be controlled by the web server user by setting the
+   * http header 'Proxy:' to some value.
+   *
+   * This can cause 'internal' http/ftp requests to be
+   * arbitrarily redirected by any external attacker.
+   */
+  if(!prox && !strcasecompare("http_proxy", proxy_env)) {
+    /* There was no lowercase variable, try the uppercase version: */
+    Curl_strntoupper(proxy_env, proxy_env, sizeof(proxy_env));
     prox=curl_getenv(proxy_env);
+  }
 
-    /*
-     * We don't try the uppercase version of HTTP_PROXY because of
-     * security reasons:
-     *
-     * When curl is used in a webserver application
-     * environment (cgi or php), this environment variable can
-     * be controlled by the web server user by setting the
-     * http header 'Proxy:' to some value.
-     *
-     * This can cause 'internal' http/ftp requests to be
-     * arbitrarily redirected by any external attacker.
-     */
-    if(!prox && !strcasecompare("http_proxy", proxy_env)) {
-      /* There was no lowercase variable, try the uppercase version: */
-      Curl_strntoupper(proxy_env, proxy_env, sizeof(proxy_env));
-      prox=curl_getenv(proxy_env);
-    }
-
-    if(prox)
-      proxy = prox; /* use this */
-    else {
-      proxy = curl_getenv("all_proxy"); /* default proxy to use */
-      if(!proxy)
-        proxy=curl_getenv("ALL_PROXY");
-    }
-  } /* if(!check_noproxy(conn->host.name, no_proxy)) - it wasn't specified
-       non-proxy */
-  free(no_proxy);
-
-#else /* !CURL_DISABLE_HTTP */
-
-  (void)conn;
-#endif /* CURL_DISABLE_HTTP */
+  if(prox)
+    proxy = prox; /* use this */
+  else {
+    proxy = curl_getenv("all_proxy"); /* default proxy to use */
+    if(!proxy)
+      proxy=curl_getenv("ALL_PROXY");
+  }
 
   return proxy;
 }
+#endif /* CURL_DISABLE_HTTP */
 
 /*
  * If this is supposed to use a proxy, we need to figure out the proxy
@@ -5032,15 +5115,19 @@ static CURLcode parse_proxy(struct Curl_easy *data,
          with reserved characters like ':' in them. */
       Curl_safefree(proxyinfo->user);
       proxyinfo->user = curl_easy_unescape(data, proxyuser, 0, NULL);
+      Curl_safefree(proxyuser);
 
-      if(!proxyinfo->user)
+      if(!proxyinfo->user) {
+        Curl_safefree(proxypasswd);
         return CURLE_OUT_OF_MEMORY;
+      }
 
       Curl_safefree(proxyinfo->passwd);
       if(proxypasswd && strlen(proxypasswd) < MAX_CURL_PASSWORD_LENGTH)
         proxyinfo->passwd = curl_easy_unescape(data, proxypasswd, 0, NULL);
       else
         proxyinfo->passwd = strdup("");
+      Curl_safefree(proxypasswd);
 
       if(!proxyinfo->passwd)
         return CURLE_OUT_OF_MEMORY;
@@ -5097,6 +5184,168 @@ static CURLcode parse_proxy_auth(struct Curl_easy *data,
                             NULL, FALSE);
   return result;
 }
+
+/* create_conn helper to parse and init proxy values. to be called after unix
+   socket init but before any proxy vars are evaluated. */
+static CURLcode create_conn_helper_init_proxy(struct connectdata *conn)
+{
+  char *proxy = NULL;
+  char *socksproxy = NULL;
+  char *no_proxy = NULL;
+  CURLcode result = CURLE_OK;
+  struct Curl_easy *data = conn->data;
+
+  /*************************************************************
+   * Extract the user and password from the authentication string
+   *************************************************************/
+  if(conn->bits.proxy_user_passwd) {
+    result = parse_proxy_auth(data, conn);
+    if(result)
+      goto out;
+  }
+
+  /*************************************************************
+   * Detect what (if any) proxy to use
+   *************************************************************/
+  if(data->set.str[STRING_PROXY]) {
+    proxy = strdup(data->set.str[STRING_PROXY]);
+    /* if global proxy is set, this is it */
+    if(NULL == proxy) {
+      failf(data, "memory shortage");
+      result = CURLE_OUT_OF_MEMORY;
+      goto out;
+    }
+  }
+
+  if(data->set.str[STRING_PRE_PROXY]) {
+    socksproxy = strdup(data->set.str[STRING_PRE_PROXY]);
+    /* if global socks proxy is set, this is it */
+    if(NULL == socksproxy) {
+      failf(data, "memory shortage");
+      result = CURLE_OUT_OF_MEMORY;
+      goto out;
+    }
+  }
+
+  no_proxy = curl_getenv("no_proxy");
+  if(!no_proxy)
+    no_proxy = curl_getenv("NO_PROXY");
+
+  if(check_noproxy(conn->host.name, data->set.str[STRING_NOPROXY]) ||
+     (!data->set.str[STRING_NOPROXY] &&
+      check_noproxy(conn->host.name, no_proxy))) {
+    Curl_safefree(proxy);
+    Curl_safefree(socksproxy);
+  }
+  else if(!proxy && !socksproxy)
+#ifndef CURL_DISABLE_HTTP
+    /* if the host is not in the noproxy list, detect proxy. */
+    proxy = detect_proxy(conn);
+#else  /* !CURL_DISABLE_HTTP */
+    proxy = NULL;
+#endif /* CURL_DISABLE_HTTP */
+
+  Curl_safefree(no_proxy);
+
+#ifdef USE_UNIX_SOCKETS
+  /* For the time being do not mix proxy and unix domain sockets. See #1274 */
+  if(proxy && conn->unix_domain_socket) {
+    free(proxy);
+    proxy = NULL;
+  }
+#endif
+
+  if(proxy && (!*proxy || (conn->handler->flags & PROTOPT_NONETWORK))) {
+    free(proxy);  /* Don't bother with an empty proxy string or if the
+                     protocol doesn't work with network */
+    proxy = NULL;
+  }
+  if(socksproxy && (!*socksproxy ||
+                    (conn->handler->flags & PROTOPT_NONETWORK))) {
+    free(socksproxy);  /* Don't bother with an empty socks proxy string or if
+                          the protocol doesn't work with network */
+    socksproxy = NULL;
+  }
+
+  /***********************************************************************
+   * If this is supposed to use a proxy, we need to figure out the proxy host
+   * name, proxy type and port number, so that we can re-use an existing
+   * connection that may exist registered to the same proxy host.
+   ***********************************************************************/
+  if(proxy || socksproxy) {
+    if(proxy) {
+      result = parse_proxy(data, conn, proxy, conn->http_proxy.proxytype);
+      Curl_safefree(proxy); /* parse_proxy copies the proxy string */
+      if(result)
+        goto out;
+    }
+
+    if(socksproxy) {
+      result = parse_proxy(data, conn, socksproxy,
+                           conn->socks_proxy.proxytype);
+      /* parse_proxy copies the socks proxy string */
+      Curl_safefree(socksproxy);
+      if(result)
+        goto out;
+    }
+
+    if(conn->http_proxy.host.rawalloc) {
+#ifdef CURL_DISABLE_HTTP
+      /* asking for a HTTP proxy is a bit funny when HTTP is disabled... */
+      result = CURLE_UNSUPPORTED_PROTOCOL;
+      goto out;
+#else
+      /* force this connection's protocol to become HTTP if not already
+         compatible - if it isn't tunneling through */
+      if(!(conn->handler->protocol & PROTO_FAMILY_HTTP) &&
+         !conn->bits.tunnel_proxy)
+        conn->handler = &Curl_handler_http;
+
+      conn->bits.httpproxy = TRUE;
+#endif
+    }
+    else {
+      conn->bits.httpproxy = FALSE; /* not a HTTP proxy */
+      conn->bits.tunnel_proxy = FALSE; /* no tunneling if not HTTP */
+    }
+
+    if(conn->socks_proxy.host.rawalloc) {
+      if(!conn->http_proxy.host.rawalloc) {
+        /* once a socks proxy */
+        if(!conn->socks_proxy.user) {
+          conn->socks_proxy.user = conn->http_proxy.user;
+          conn->http_proxy.user = NULL;
+          Curl_safefree(conn->socks_proxy.passwd);
+          conn->socks_proxy.passwd = conn->http_proxy.passwd;
+          conn->http_proxy.passwd = NULL;
+        }
+      }
+      conn->bits.socksproxy = TRUE;
+    }
+    else
+      conn->bits.socksproxy = FALSE; /* not a socks proxy */
+  }
+  else {
+    conn->bits.socksproxy = FALSE;
+    conn->bits.httpproxy = FALSE;
+  }
+  conn->bits.proxy = conn->bits.httpproxy || conn->bits.socksproxy;
+
+  if(!conn->bits.proxy) {
+    /* we aren't using the proxy after all... */
+    conn->bits.proxy = FALSE;
+    conn->bits.httpproxy = FALSE;
+    conn->bits.socksproxy = FALSE;
+    conn->bits.proxy_user_passwd = FALSE;
+    conn->bits.tunnel_proxy = FALSE;
+  }
+
+out:
+
+  free(socksproxy);
+  free(proxy);
+  return result;
+}
 #endif /* CURL_DISABLE_PROXY */
 
 /*
@@ -5137,6 +5386,7 @@ static CURLcode parse_url_login(struct Curl_easy *data,
   DEBUGASSERT(!**user);
   DEBUGASSERT(!**passwd);
   DEBUGASSERT(!**options);
+  DEBUGASSERT(conn->handler);
 
   if(!ptr)
     goto out;
@@ -5155,9 +5405,12 @@ static CURLcode parse_url_login(struct Curl_easy *data,
   if(data->set.use_netrc == CURL_NETRC_REQUIRED)
     goto out;
 
-  /* We could use the login information in the URL so extract it */
+  /* We could use the login information in the URL so extract it. Only parse
+     options if the handler says we should. */
   result = parse_login_details(login, ptr - login - 1,
-                               &userp, &passwdp, &optionsp);
+                               &userp, &passwdp,
+                               (conn->handler->flags & PROTOPT_URLOPTIONS)?
+                               &optionsp:NULL);
   if(result)
     goto out;
 
@@ -5387,7 +5640,7 @@ static CURLcode parse_remote_port(struct Curl_easy *data,
     }
 #endif
 
-    portptr = strrchr(conn->host.name, ':');
+    portptr = strchr(conn->host.name, ':');
   }
 
   if(data->set.use_port && data->state.allow_port) {
@@ -5442,15 +5695,16 @@ static CURLcode parse_remote_port(struct Curl_easy *data,
       return CURLE_URL_MALFORMAT;
     }
 
-    else if(rest != &portptr[1]) {
+    if(rest[0]) {
+      failf(data, "Port number ended with '%c'", rest[0]);
+      return CURLE_URL_MALFORMAT;
+    }
+
+    if(rest != &portptr[1]) {
       *portptr = '\0'; /* cut off the name there */
       conn->remote_port = curlx_ultous(port);
     }
     else {
-      if(rest[0]) {
-        failf(data, "Illegal port number");
-        return CURLE_URL_MALFORMAT;
-      }
       /* Browser behavior adaptation. If there's a colon with no digits after,
          just cut off the name there which makes us ignore the colon and just
          use the default port. Firefox and Chrome both do that. */
@@ -5584,6 +5838,10 @@ static CURLcode parse_connect_to_host_port(struct Curl_easy *data,
   char *portptr;
   int port = -1;
 
+#if defined(CURL_DISABLE_VERBOSE_STRINGS)
+  (void) data;
+#endif
+
   *hostname_result = NULL;
   *port_result = -1;
 
@@ -5749,14 +6007,11 @@ static CURLcode parse_connect_to_slist(struct Curl_easy *data,
       return result;
 
     if(host && *host) {
-      bool ipv6host;
       conn->conn_to_host.rawalloc = host;
       conn->conn_to_host.name = host;
       conn->bits.conn_to_host = TRUE;
 
-      ipv6host = strchr(host, ':') != NULL;
-      infof(data, "Connecting to hostname: %s%s%s\n",
-            ipv6host ? "[" : "", host, ipv6host ? "]" : "");
+      infof(data, "Connecting to hostname: %s\n", host);
     }
     else {
       /* no "connect to host" */
@@ -5816,8 +6071,9 @@ static CURLcode resolve_server(struct Curl_easy *data,
       if(!hostaddr)
         result = CURLE_OUT_OF_MEMORY;
       else {
-        int longpath=0;
-        hostaddr->addr = Curl_unix2addr(path, &longpath);
+        bool longpath = FALSE;
+        hostaddr->addr = Curl_unix2addr(path, &longpath,
+                                        conn->abstract_unix_socket);
         if(hostaddr->addr)
           hostaddr->inuse++;
         else {
@@ -5847,7 +6103,7 @@ static CURLcode resolve_server(struct Curl_easy *data,
       if(conn->bits.conn_to_port)
         conn->port = conn->conn_to_port;
       else
-        conn->port = conn->remote_port; /* it is the same port */
+        conn->port = conn->remote_port;
 
       /* Resolve target host right on */
       rc = Curl_resolv_timeout(conn, connhost->name, (int)conn->port,
@@ -5903,11 +6159,9 @@ static void reuse_conn(struct connectdata *old_conn,
 {
   free_fixed_hostname(&old_conn->http_proxy.host);
   free_fixed_hostname(&old_conn->socks_proxy.host);
-  free_fixed_hostname(&old_conn->proxy);
 
   free(old_conn->http_proxy.host.rawalloc);
   free(old_conn->socks_proxy.host.rawalloc);
-  free(old_conn->proxy.rawalloc);
 
   /* free the SSL config struct from this connection struct as this was
      allocated in vain and is targeted for destruction */
@@ -5962,7 +6216,6 @@ static void reuse_conn(struct connectdata *old_conn,
   Curl_persistconninfo(conn);
 
   conn_reset_all_postponed_data(old_conn); /* free buffers */
-  conn_reset_all_postponed_data(conn);     /* reset unprocessed data */
 
   /* re-use init */
   conn->bits.reuse = TRUE; /* yes, we're re-using here */
@@ -5975,11 +6228,8 @@ static void reuse_conn(struct connectdata *old_conn,
   Curl_safefree(old_conn->socks_proxy.passwd);
   Curl_safefree(old_conn->localdev);
 
-  Curl_llist_destroy(old_conn->send_pipe, NULL);
-  Curl_llist_destroy(old_conn->recv_pipe, NULL);
-
-  old_conn->send_pipe = NULL;
-  old_conn->recv_pipe = NULL;
+  Curl_llist_destroy(&old_conn->send_pipe, NULL);
+  Curl_llist_destroy(&old_conn->recv_pipe, NULL);
 
   Curl_safefree(old_conn->master_buffer);
 
@@ -6016,8 +6266,6 @@ static CURLcode create_conn(struct Curl_easy *data,
   char *passwd = NULL;
   char *options = NULL;
   bool reuse;
-  char *proxy = NULL;
-  char *socksproxy = NULL;
   bool prot_missing = FALSE;
   bool connections_available = TRUE;
   bool force_reuse = FALSE;
@@ -6161,147 +6409,24 @@ static CURLcode create_conn(struct Curl_easy *data,
     }
   }
 
-#ifndef CURL_DISABLE_PROXY
-  /*************************************************************
-   * Extract the user and password from the authentication string
-   *************************************************************/
-  if(conn->bits.proxy_user_passwd) {
-    result = parse_proxy_auth(data, conn);
-    if(result)
-      goto out;
-  }
-
-  /*************************************************************
-   * Detect what (if any) proxy to use
-   *************************************************************/
-  if(data->set.str[STRING_PROXY]) {
-    proxy = strdup(data->set.str[STRING_PROXY]);
-    /* if global proxy is set, this is it */
-    if(NULL == proxy) {
-      failf(data, "memory shortage");
-      result = CURLE_OUT_OF_MEMORY;
-      goto out;
-    }
-  }
-
-  if(data->set.str[STRING_PRE_PROXY]) {
-    socksproxy = strdup(data->set.str[STRING_PRE_PROXY]);
-    /* if global socks proxy is set, this is it */
-    if(NULL == socksproxy) {
-      failf(data, "memory shortage");
-      result = CURLE_OUT_OF_MEMORY;
-      goto out;
-    }
-  }
-
-  if(data->set.str[STRING_NOPROXY] &&
-     check_noproxy(conn->host.name, data->set.str[STRING_NOPROXY])) {
-    Curl_safefree(proxy);
-    Curl_safefree(socksproxy);
-  }
-  else if(!proxy && !socksproxy)
-    proxy = detect_proxy(conn);
-
 #ifdef USE_UNIX_SOCKETS
   if(data->set.str[STRING_UNIX_SOCKET_PATH]) {
-    if(proxy) {
-      free(proxy); /* Unix domain sockets cannot be proxied, so disable it */
-      proxy = NULL;
-    }
     conn->unix_domain_socket = strdup(data->set.str[STRING_UNIX_SOCKET_PATH]);
     if(conn->unix_domain_socket == NULL) {
       result = CURLE_OUT_OF_MEMORY;
       goto out;
     }
+    conn->abstract_unix_socket = data->set.abstract_unix_socket;
   }
 #endif
 
-  if(proxy && (!*proxy || (conn->handler->flags & PROTOPT_NONETWORK))) {
-    free(proxy);  /* Don't bother with an empty proxy string or if the
-                     protocol doesn't work with network */
-    proxy = NULL;
-  }
-  if(socksproxy && (!*socksproxy ||
-                    (conn->handler->flags & PROTOPT_NONETWORK))) {
-    free(socksproxy);  /* Don't bother with an empty socks proxy string or if
-                          the protocol doesn't work with network */
-    socksproxy = NULL;
-  }
-
-  /***********************************************************************
-   * If this is supposed to use a proxy, we need to figure out the proxy host
-   * name, proxy type and port number, so that we can re-use an existing
-   * connection that may exist registered to the same proxy host.
-   ***********************************************************************/
-  if(proxy || socksproxy) {
-    if(proxy) {
-      result = parse_proxy(data, conn, proxy, conn->http_proxy.proxytype);
-      Curl_safefree(proxy); /* parse_proxy copies the proxy string */
-      if(result)
-        goto out;
-    }
-
-    if(socksproxy) {
-      result = parse_proxy(data, conn, socksproxy,
-                           conn->socks_proxy.proxytype);
-      /* parse_proxy copies the socks proxy string */
-      Curl_safefree(socksproxy);
-      if(result)
-        goto out;
-    }
-
-    if(conn->http_proxy.host.rawalloc) {
-#ifdef CURL_DISABLE_HTTP
-      /* asking for a HTTP proxy is a bit funny when HTTP is disabled... */
-      result = CURLE_UNSUPPORTED_PROTOCOL;
-      goto out;
-#else
-      /* force this connection's protocol to become HTTP if not already
-         compatible - if it isn't tunneling through */
-      if(!(conn->handler->protocol & PROTO_FAMILY_HTTP) &&
-         !conn->bits.tunnel_proxy)
-        conn->handler = &Curl_handler_http;
-
-      conn->bits.httpproxy = TRUE;
+  /* After the unix socket init but before the proxy vars are used, parse and
+     initialize the proxy vars */
+#ifndef CURL_DISABLE_PROXY
+  result = create_conn_helper_init_proxy(conn);
+  if(result)
+    goto out;
 #endif
-    }
-    else {
-      conn->bits.httpproxy = FALSE; /* not a HTTP proxy */
-      conn->bits.tunnel_proxy = FALSE; /* no tunneling if not HTTP */
-    }
-
-    if(conn->socks_proxy.host.rawalloc) {
-      if(!conn->http_proxy.host.rawalloc) {
-        /* once a socks proxy */
-        if(!conn->socks_proxy.user) {
-          conn->socks_proxy.user = conn->http_proxy.user;
-          conn->http_proxy.user = NULL;
-          Curl_safefree(conn->socks_proxy.passwd);
-          conn->socks_proxy.passwd = conn->http_proxy.passwd;
-          conn->http_proxy.passwd = NULL;
-        }
-      }
-      conn->bits.socksproxy = TRUE;
-    }
-    else
-      conn->bits.socksproxy = FALSE; /* not a socks proxy */
-  }
-  else {
-    conn->bits.socksproxy = FALSE;
-    conn->bits.httpproxy = FALSE;
-  }
-  conn->bits.proxy = conn->bits.httpproxy || conn->bits.socksproxy;
-
-  if(!conn->bits.proxy) {
-    /* we aren't using the proxy after all... */
-    conn->bits.proxy = FALSE;
-    conn->bits.httpproxy = FALSE;
-    conn->bits.socksproxy = FALSE;
-    conn->bits.proxy_user_passwd = FALSE;
-    conn->bits.tunnel_proxy = FALSE;
-  }
-
-#endif /* CURL_DISABLE_PROXY */
 
   /*************************************************************
    * If the protocol is using SSL and HTTP proxy is used, we set
@@ -6340,12 +6465,14 @@ static CURLcode create_conn(struct Curl_easy *data,
   fix_hostname(conn, &conn->host);
   if(conn->bits.conn_to_host)
     fix_hostname(conn, &conn->conn_to_host);
-  if(conn->proxy.name && *conn->proxy.name)
-    fix_hostname(conn, &conn->proxy);
+  if(conn->bits.httpproxy)
+    fix_hostname(conn, &conn->http_proxy.host);
+  if(conn->bits.socksproxy)
+    fix_hostname(conn, &conn->socks_proxy.host);
 
   /*************************************************************
    * Check whether the host and the "connect to host" are equal.
-   * Do this after the hostnames have been IDN-fixed .
+   * Do this after the hostnames have been IDN-fixed.
    *************************************************************/
   if(conn->bits.conn_to_host &&
      strcasecompare(conn->conn_to_host.name, conn->host.name)) {
@@ -6501,7 +6628,7 @@ static CURLcode create_conn(struct Curl_easy *data,
   /* If we found a reusable connection, we may still want to
      open a new connection if we are pipelining. */
   if(reuse && !force_reuse && IsPipeliningPossible(data, conn_temp)) {
-    size_t pipelen = conn_temp->send_pipe->size + conn_temp->recv_pipe->size;
+    size_t pipelen = conn_temp->send_pipe.size + conn_temp->recv_pipe.size;
     if(pipelen > 0) {
       infof(data, "Found connection %ld, with requests in the pipe (%zu)\n",
             conn_temp->connection_id, pipelen);
@@ -6661,13 +6788,11 @@ static CURLcode create_conn(struct Curl_easy *data,
    *************************************************************/
   result = resolve_server(data, conn, async);
 
-  out:
+out:
 
   free(options);
   free(passwd);
   free(user);
-  free(socksproxy);
-  free(proxy);
   return result;
 }
 
@@ -6771,7 +6896,7 @@ CURLcode Curl_connect(struct Curl_easy *data,
 
   if(!result) {
     /* no error */
-    if((*in_connect)->send_pipe->size || (*in_connect)->recv_pipe->size)
+    if((*in_connect)->send_pipe.size || (*in_connect)->recv_pipe.size)
       /* pipelining */
       *protocol_done = TRUE;
     else if(!*asyncp) {