@@ -140,6 +140,19 @@ static CURLcode parse_login_details(const char *login, const size_t len,
                                     char **optionsptr);
 static unsigned int get_protocol_family(unsigned int protocol);
 
+#define READBUFFER_SIZE CURL_MAX_WRITE_SIZE
+#define READBUFFER_MAX  CURL_MAX_READ_SIZE
+#define READBUFFER_MIN  1024
+
+/* Some parts of the code (e.g. chunked encoding) assume this buffer has at
+ * more than just a few bytes to play with. Don't let it become too small or
+ * bad things will happen.
+ */
+#if READBUFFER_SIZE < READBUFFER_MIN
+# error READBUFFER_SIZE is too small
+#endif
+
+
 /*
  * Protocol table.
  */
@@ -607,6 +620,7 @@ CURLcode Curl_init_userdefined(struct UserDefined *set)
 
   set->expect_100_timeout = 1000L; /* Wait for a second by default. */
   set->sep_headers = TRUE; /* separated header lists by default */
+  set->buffer_size = READBUFFER_SIZE;
 
   Curl_http2_init_userset(set);
   return result;
@@ -644,7 +658,7 @@ CURLcode Curl_open(struct Curl_easy **curl)
 
   /* We do some initial setup here, all those fields that can't be just 0 */
 
-  data->state.buffer = malloc(BUFSIZE + 1);
+  data->state.buffer = malloc(READBUFFER_SIZE + 1);
   if(!data->state.buffer) {
     DEBUGF(fprintf(stderr, "Error: malloc of buffer failed\n"));
     result = CURLE_OUT_OF_MEMORY;
@@ -1009,8 +1023,8 @@ CURLcode Curl_setopt(struct Curl_easy *data, CURLoption option,
      * CURL_REDIR_POST_ALL - POST is kept as POST after 301, 302 and 303
      * other - POST is kept as POST after 301 and 302
      */
-    int postRedir = curlx_sltosi(va_arg(param, long));
-    data->set.keep_post = postRedir & CURL_REDIR_POST_ALL;
+    arg = va_arg(param, long);
+    data->set.keep_post = arg & CURL_REDIR_POST_ALL;
   }
   break;
 
@@ -2061,13 +2075,19 @@ CURLcode Curl_setopt(struct Curl_easy *data, CURLoption option,
     /*
      * Set what local port to bind the socket to when performing an operation.
      */
-    data->set.localport = curlx_sltous(va_arg(param, long));
+    arg = va_arg(param, long);
+    if((arg < 0) || (arg > 65535))
+      return CURLE_BAD_FUNCTION_ARGUMENT;
+    data->set.localport = curlx_sltous(arg);
     break;
   case CURLOPT_LOCALPORTRANGE:
     /*
      * Set number of local ports to try, starting with CURLOPT_LOCALPORT.
      */
-    data->set.localportrange = curlx_sltosi(va_arg(param, long));
+    arg = va_arg(param, long);
+    if((arg < 0) || (arg > 65535))
+      return CURLE_BAD_FUNCTION_ARGUMENT;
+    data->set.localportrange = curlx_sltosi(arg);
     break;
   case CURLOPT_KRBLEVEL:
     /*
@@ -2284,22 +2304,26 @@ CURLcode Curl_setopt(struct Curl_easy *data, CURLoption option,
      * The application kindly asks for a differently sized receive buffer.
      * If it seems reasonable, we'll use it.
      */
-    data->set.buffer_size = va_arg(param, long);
-
-    if(data->set.buffer_size > MAX_BUFSIZE)
-      data->set.buffer_size = MAX_BUFSIZE; /* huge internal default */
-    else if(data->set.buffer_size < 1)
-      data->set.buffer_size = BUFSIZE;
+    arg = va_arg(param, long);
 
-    /* Resize only if larger than default buffer size. */
-    if(data->set.buffer_size > BUFSIZE) {
-      data->state.buffer = realloc(data->state.buffer,
-                                   data->set.buffer_size + 1);
-      if(!data->state.buffer) {
+    if(arg > READBUFFER_MAX)
+      arg = READBUFFER_MAX;
+    else if(arg < 1)
+      arg = READBUFFER_SIZE;
+    else if(arg < READBUFFER_MIN)
+      arg = READBUFFER_MIN;
+
+    /* Resize if new size */
+    if(arg != data->set.buffer_size) {
+      char *newbuff = realloc(data->state.buffer, arg + 1);
+      if(!newbuff) {
         DEBUGF(fprintf(stderr, "Error: realloc of buffer failed\n"));
         result = CURLE_OUT_OF_MEMORY;
       }
+      else
+        data->state.buffer = newbuff;
     }
+    data->set.buffer_size = arg;
 
     break;
 
@@ -2592,7 +2616,10 @@ CURLcode Curl_setopt(struct Curl_easy *data, CURLoption option,
      * know that an unsigned int will always hold the value so we blindly
      * typecast to this type
      */
-    data->set.scope_id = curlx_sltoui(va_arg(param, long));
+    arg = va_arg(param, long);
+    if((arg < 0) || (arg > 0xf))
+      return CURLE_BAD_FUNCTION_ARGUMENT;
+    data->set.scope_id = curlx_sltoui(arg);
     break;
 
   case CURLOPT_PROTOCOLS:
@@ -2794,13 +2821,17 @@ CURLcode Curl_setopt(struct Curl_easy *data, CURLoption option,
       data->set.proxy_ssl.authtype = CURL_TLSAUTH_SRP; /* default to SRP */
     break;
   case CURLOPT_TLSAUTH_TYPE:
-    if(strncasecompare((char *)va_arg(param, char *), "SRP", strlen("SRP")))
+    argptr = va_arg(param, char *);
+    if(!argptr ||
+       strncasecompare(argptr, "SRP", strlen("SRP")))
       data->set.ssl.authtype = CURL_TLSAUTH_SRP;
     else
       data->set.ssl.authtype = CURL_TLSAUTH_NONE;
     break;
   case CURLOPT_PROXY_TLSAUTH_TYPE:
-    if(strncasecompare((char *)va_arg(param, char *), "SRP", strlen("SRP")))
+    argptr = va_arg(param, char *);
+    if(!argptr ||
+       strncasecompare(argptr, "SRP", strlen("SRP")))
       data->set.proxy_ssl.authtype = CURL_TLSAUTH_SRP;
     else
       data->set.proxy_ssl.authtype = CURL_TLSAUTH_NONE;
@@ -2935,8 +2966,7 @@ static void conn_reset_all_postponed_data(struct connectdata *conn)
   conn_reset_postponed_data(conn, 1);
 }
 #else  /* ! USE_RECV_BEFORE_SEND_WORKAROUND */
-/* Use "do-nothing" macros instead of functions when workaround not used */
-#define conn_reset_postponed_data(c,n) do {} WHILE_FALSE
+/* Use "do-nothing" macro instead of function when workaround not used */
 #define conn_reset_all_postponed_data(c) do {} WHILE_FALSE
 #endif /* ! USE_RECV_BEFORE_SEND_WORKAROUND */
 
@@ -2993,6 +3023,7 @@ static void conn_free(struct connectdata *conn)
   Curl_safefree(conn->http_proxy.host.rawalloc); /* http proxy name buffer */
   Curl_safefree(conn->socks_proxy.host.rawalloc); /* socks proxy name buffer */
   Curl_safefree(conn->master_buffer);
+  Curl_safefree(conn->connect_buffer);
 
   conn_reset_all_postponed_data(conn);
 
@@ -3100,12 +3131,16 @@ static bool SocketIsDead(curl_socket_t sock)
 }
 
 /*
- * IsPipeliningPossible() returns TRUE if the options set would allow
- * pipelining/multiplexing and the connection is using a HTTP protocol.
+ * IsPipeliningPossible()
+ *
+ * Return a bitmask with the available pipelining and multiplexing options for
+ * the given requested connection.
  */
-static bool IsPipeliningPossible(const struct Curl_easy *handle,
-                                 const struct connectdata *conn)
+static int IsPipeliningPossible(const struct Curl_easy *handle,
+                                const struct connectdata *conn)
 {
+  int avail = 0;
+
   /* If a HTTP protocol and pipelining is enabled */
   if((conn->handler->protocol & PROTO_FAMILY_HTTP) &&
      (!conn->bits.protoconnstart || !conn->bits.close)) {
@@ -3115,14 +3150,14 @@ static bool IsPipeliningPossible(const struct Curl_easy *handle,
        (handle->set.httpreq == HTTPREQ_GET ||
         handle->set.httpreq == HTTPREQ_HEAD))
       /* didn't ask for HTTP/1.0 and a GET or HEAD */
-      return TRUE;
+      avail |= CURLPIPE_HTTP1;
 
     if(Curl_pipeline_wanted(handle->multi, CURLPIPE_MULTIPLEX) &&
        (handle->set.httpversion >= CURL_HTTP_VERSION_2))
       /* allows HTTP/2 */
-      return TRUE;
+      avail |= CURLPIPE_MULTIPLEX;
   }
-  return FALSE;
+  return avail;
 }
 
 int Curl_removeHandleFromPipeline(struct Curl_easy *handle,
@@ -3409,7 +3444,7 @@ ConnectionExists(struct Curl_easy *data,
   struct connectdata *check;
   struct connectdata *chosen = 0;
   bool foundPendingCandidate = FALSE;
-  bool canPipeline = IsPipeliningPossible(data, needle);
+  int canpipe = IsPipeliningPossible(data, needle);
   struct connectbundle *bundle;
 
 #ifdef USE_NTLM
@@ -3425,10 +3460,10 @@ ConnectionExists(struct Curl_easy *data,
   *force_reuse = FALSE;
   *waitpipe = FALSE;
 
-  /* We can't pipe if the site is blacklisted */
-  if(canPipeline && Curl_pipeline_site_blacklisted(data, needle)) {
-    canPipeline = FALSE;
-  }
+  /* We can't pipeline if the site is blacklisted */
+  if((canpipe & CURLPIPE_HTTP1) &&
+     Curl_pipeline_site_blacklisted(data, needle))
+    canpipe &= ~ CURLPIPE_HTTP1;
 
   /* Look up the bundle with all the connections to this
      particular host */
@@ -3448,8 +3483,8 @@ ConnectionExists(struct Curl_easy *data,
            (bundle->multiuse == BUNDLE_MULTIPLEX ?
             "can multiplex" : "serially")));
 
-    /* We can't pipe if we don't know anything about the server */
-    if(canPipeline) {
+    /* We can't pipeline if we don't know anything about the server */
+    if(canpipe) {
       if(bundle->multiuse <= BUNDLE_UNKNOWN) {
         if((bundle->multiuse == BUNDLE_UNKNOWN) && data->set.pipewait) {
           infof(data, "Server doesn't support multi-use yet, wait\n");
@@ -3458,18 +3493,18 @@ ConnectionExists(struct Curl_easy *data,
         }
 
         infof(data, "Server doesn't support multi-use (yet)\n");
-        canPipeline = FALSE;
+        canpipe = 0;
       }
       if((bundle->multiuse == BUNDLE_PIPELINING) &&
          !Curl_pipeline_wanted(data->multi, CURLPIPE_HTTP1)) {
         /* not asked for, switch off */
         infof(data, "Could pipeline, but not asked to!\n");
-        canPipeline = FALSE;
+        canpipe = 0;
       }
       else if((bundle->multiuse == BUNDLE_MULTIPLEX) &&
               !Curl_pipeline_wanted(data->multi, CURLPIPE_MULTIPLEX)) {
         infof(data, "Could multiplex, but not asked to!\n");
-        canPipeline = FALSE;
+        canpipe = 0;
       }
     }
 
@@ -3490,20 +3525,21 @@ ConnectionExists(struct Curl_easy *data,
 
       pipeLen = check->send_pipe.size + check->recv_pipe.size;
 
-      if(canPipeline) {
+      if(canpipe) {
         if(check->bits.protoconnstart && check->bits.close)
           continue;
 
         if(!check->bits.multiplex) {
-          /* If not multiplexing, make sure the pipe has only GET requests */
+          /* If not multiplexing, make sure the connection is fine for HTTP/1
+             pipelining */
           struct Curl_easy* sh = gethandleathead(&check->send_pipe);
           struct Curl_easy* rh = gethandleathead(&check->recv_pipe);
           if(sh) {
-            if(!IsPipeliningPossible(sh, check))
+            if(!(IsPipeliningPossible(sh, check) & CURLPIPE_HTTP1))
               continue;
           }
           else if(rh) {
-            if(!IsPipeliningPossible(rh, check))
+            if(!(IsPipeliningPossible(rh, check) & CURLPIPE_HTTP1))
               continue;
           }
         }
@@ -3611,7 +3647,7 @@ ConnectionExists(struct Curl_easy *data,
         }
       }
 
-      if(!canPipeline && check->inuse)
+      if(!canpipe && check->inuse)
         /* this request can't be pipelined but the checked connection is
            already in use so we skip it */
         continue;
@@ -3742,7 +3778,7 @@ ConnectionExists(struct Curl_easy *data,
           continue;
         }
 #endif
-        if(canPipeline) {
+        if(canpipe) {
           /* We can pipeline if we want to. Let's continue looking for
              the optimal connection to use, i.e the shortest pipe that is not
              blacklisted. */
@@ -4203,7 +4239,7 @@ static struct connectdata *allocate_conn(struct Curl_easy *data)
   if(Curl_pipeline_wanted(data->multi, CURLPIPE_HTTP1) &&
      !conn->master_buffer) {
     /* Allocate master_buffer to be used for HTTP/1 pipelining */
-    conn->master_buffer = calloc(BUFSIZE, sizeof(char));
+    conn->master_buffer = calloc(MASTERBUF_SIZE, sizeof(char));
     if(!conn->master_buffer)
       goto error;
   }
@@ -4430,6 +4466,7 @@ static CURLcode parseurlandfillconn(struct Curl_easy *data,
 #endif
 
     protop = "file"; /* protocol string */
+    *prot_missing = !url_has_scheme;
   }
   else {
     /* clear path */
@@ -4593,14 +4630,30 @@ static CURLcode parseurlandfillconn(struct Curl_easy *data,
 
     size_t plen = strlen(path); /* new path, should be 1 byte longer than
                                    the original */
-    size_t urllen = strlen(data->change.url); /* original URL length */
-
     size_t prefixlen = strlen(conn->host.name);
 
-    if(!*prot_missing)
-      prefixlen += strlen(protop) + strlen("://");
+    if(!*prot_missing) {
+      size_t protolen = strlen(protop);
+
+      if(curl_strnequal(protop, data->change.url, protolen))
+        prefixlen += protolen;
+      else {
+        failf(data, "<url> malformed");
+        return CURLE_URL_MALFORMAT;
+      }
+
+      if(curl_strnequal("://", &data->change.url[protolen], 3))
+        prefixlen += 3;
+      /* only file: is allowed to omit one or both slashes */
+      else if(curl_strnequal("file:", data->change.url, 5))
+        prefixlen += 1 + (data->change.url[5] == '/');
+      else {
+        failf(data, "<url> malformed");
+        return CURLE_URL_MALFORMAT;
+      }
+    }
 
-    reurl = malloc(urllen + 2); /* 2 for zerobyte + slash */
+    reurl = malloc(prefixlen + plen + 1);
     if(!reurl)
       return CURLE_OUT_OF_MEMORY;
 
@@ -6961,7 +7014,6 @@ CURLcode Curl_init_do(struct Curl_easy *data, struct connectdata *conn)
   k->bytecount = 0;
 
   k->buf = data->state.buffer;
-  k->uploadbuf = data->state.uploadbuffer;
   k->hbufp = data->state.headerbuff;
   k->ignorebody=FALSE;
 
@@ -6985,7 +7037,7 @@ CURLcode Curl_init_do(struct Curl_easy *data, struct connectdata *conn)
 * Returns the family as a single bit protocol identifier.
 */
 
-unsigned int get_protocol_family(unsigned int protocol)
+static unsigned int get_protocol_family(unsigned int protocol)
 {
   unsigned int family;
 