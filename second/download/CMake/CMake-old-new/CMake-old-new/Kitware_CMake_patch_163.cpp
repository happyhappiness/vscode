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
@@ -54,9 +54,10 @@
 #include "curl_base64.h"
 #include "cookie.h"
 #include "strequal.h"
+#include "vauth/vauth.h"
 #include "vtls/vtls.h"
 #include "http_digest.h"
-#include "curl_ntlm.h"
+#include "http_ntlm.h"
 #include "curl_ntlm_wb.h"
 #include "http_negotiate.h"
 #include "url.h"
@@ -76,9 +77,9 @@
 #include "pipeline.h"
 #include "http2.h"
 #include "connect.h"
-#include "curl_printf.h"
 
-/* The last #include files should be: */
+/* The last 3 #include files should be in this order */
+#include "curl_printf.h"
 #include "curl_memory.h"
 #include "memdebug.h"
 
@@ -144,14 +145,13 @@ const struct Curl_handler Curl_handler_https = {
   ZERO_NULL,                            /* readwrite */
   PORT_HTTPS,                           /* defport */
   CURLPROTO_HTTPS,                      /* protocol */
-  PROTOPT_SSL | PROTOPT_CREDSPERREQUEST /* flags */
+  PROTOPT_SSL | PROTOPT_CREDSPERREQUEST | PROTOPT_ALPN_NPN /* flags */
 };
 #endif
 
-
 CURLcode Curl_http_setup_conn(struct connectdata *conn)
 {
-  /* allocate the HTTP-specific struct for the SessionHandle, only to survive
+  /* allocate the HTTP-specific struct for the Curl_easy, only to survive
      during this request */
   struct HTTP *http;
   DEBUGASSERT(conn->data->req.protop == NULL);
@@ -179,12 +179,13 @@ char *Curl_checkheaders(const struct connectdata *conn,
 {
   struct curl_slist *head;
   size_t thislen = strlen(thisheader);
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
 
   for(head = data->set.headers;head; head=head->next) {
     if(Curl_raw_nequal(head->data, thisheader, thislen))
       return head->data;
   }
+
   return NULL;
 }
 
@@ -193,24 +194,24 @@ char *Curl_checkheaders(const struct connectdata *conn,
  * if proxy headers are not available, then it will lookup into http header
  * link list
  *
- * It takes a connectdata struct as input instead of the SessionHandle simply
+ * It takes a connectdata struct as input instead of the Curl_easy simply
  * to know if this is a proxy request or not, as it then might check a
  * different header list.
- *
  */
 char *Curl_checkProxyheaders(const struct connectdata *conn,
                              const char *thisheader)
 {
   struct curl_slist *head;
   size_t thislen = strlen(thisheader);
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
 
-  for(head = (conn->bits.proxy && data->set.sep_headers)?
-        data->set.proxyheaders:data->set.headers;
+  for(head = (conn->bits.proxy && data->set.sep_headers) ?
+        data->set.proxyheaders : data->set.headers;
       head; head=head->next) {
     if(Curl_raw_nequal(head->data, thisheader, thislen))
       return head->data;
   }
+
   return NULL;
 }
 
@@ -279,7 +280,7 @@ static CURLcode http_output_basic(struct connectdata *conn, bool proxy)
 {
   size_t size = 0;
   char *authorization = NULL;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   char **userp;
   const char *user;
   const char *pwd;
@@ -309,7 +310,7 @@ static CURLcode http_output_basic(struct connectdata *conn, bool proxy)
 
   free(*userp);
   *userp = aprintf("%sAuthorization: Basic %s\r\n",
-                   proxy?"Proxy-":"",
+                   proxy ? "Proxy-" : "",
                    authorization);
   free(authorization);
   if(!*userp)
@@ -376,7 +377,7 @@ static bool pickoneauth(struct auth *pick)
  */
 static CURLcode http_perhapsrewind(struct connectdata *conn)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct HTTP *http = data->req.protop;
   curl_off_t bytessent;
   curl_off_t expectsend = -1; /* default is unknown */
@@ -484,7 +485,7 @@ static CURLcode http_perhapsrewind(struct connectdata *conn)
 
 CURLcode Curl_http_auth_act(struct connectdata *conn)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   bool pickhost = FALSE;
   bool pickproxy = FALSE;
   CURLcode result = CURLE_OK;
@@ -528,7 +529,6 @@ CURLcode Curl_http_auth_act(struct connectdata *conn)
         return result;
     }
   }
-
   else if((data->req.httpcode < 300) &&
           (!data->state.authhost.done) &&
           conn->bits.authneg) {
@@ -553,7 +553,6 @@ CURLcode Curl_http_auth_act(struct connectdata *conn)
   return result;
 }
 
-
 /*
  * Output the correct authentication header depending on the auth type
  * and whether or not it is to a proxy.
@@ -567,12 +566,12 @@ output_auth_headers(struct connectdata *conn,
 {
   const char *auth = NULL;
   CURLcode result = CURLE_OK;
-#if defined(USE_SPNEGO) || !defined(CURL_DISABLE_VERBOSE_STRINGS)
-  struct SessionHandle *data = conn->data;
+#if !defined(CURL_DISABLE_VERBOSE_STRINGS) || defined(USE_SPNEGO)
+  struct Curl_easy *data = conn->data;
 #endif
 #ifdef USE_SPNEGO
-  struct negotiatedata *negdata = proxy?
-    &data->state.proxyneg:&data->state.negotiate;
+  struct negotiatedata *negdata = proxy ?
+    &data->state.proxyneg : &data->state.negotiate;
 #endif
 
 #ifdef CURL_DISABLE_CRYPTO_AUTH
@@ -584,7 +583,7 @@ output_auth_headers(struct connectdata *conn,
   negdata->state = GSS_AUTHNONE;
   if((authstatus->picked == CURLAUTH_NEGOTIATE) &&
      negdata->context && !GSS_ERROR(negdata->status)) {
-    auth="Negotiate";
+    auth = "Negotiate";
     result = Curl_output_negotiate(conn, proxy);
     if(result)
       return result;
@@ -595,7 +594,7 @@ output_auth_headers(struct connectdata *conn,
 #endif
 #ifdef USE_NTLM
   if(authstatus->picked == CURLAUTH_NTLM) {
-    auth="NTLM";
+    auth = "NTLM";
     result = Curl_output_ntlm(conn, proxy);
     if(result)
       return result;
@@ -613,7 +612,7 @@ output_auth_headers(struct connectdata *conn,
 #endif
 #ifndef CURL_DISABLE_CRYPTO_AUTH
   if(authstatus->picked == CURLAUTH_DIGEST) {
-    auth="Digest";
+    auth = "Digest";
     result = Curl_output_digest(conn,
                                 proxy,
                                 (const unsigned char *)request,
@@ -629,21 +628,22 @@ output_auth_headers(struct connectdata *conn,
         !Curl_checkProxyheaders(conn, "Proxy-authorization:")) ||
        (!proxy && conn->bits.user_passwd &&
         !Curl_checkheaders(conn, "Authorization:"))) {
-      auth="Basic";
+      auth = "Basic";
       result = http_output_basic(conn, proxy);
       if(result)
         return result;
     }
+
     /* NOTE: this function should set 'done' TRUE, as the other auth
        functions work that way */
     authstatus->done = TRUE;
   }
 
   if(auth) {
     infof(data, "%s auth using %s with user '%s'\n",
-          proxy?"Proxy":"Server", auth,
-          proxy?(conn->proxyuser?conn->proxyuser:""):
-                (conn->user?conn->user:""));
+          proxy ? "Proxy" : "Server", auth,
+          proxy ? (conn->proxyuser ? conn->proxyuser : "") :
+                  (conn->user ? conn->user : ""));
     authstatus->multi = (!authstatus->done) ? TRUE : FALSE;
   }
   else
@@ -674,7 +674,7 @@ Curl_http_output_auth(struct connectdata *conn,
                                            up the proxy tunnel */
 {
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct auth *authhost;
   struct auth *authproxy;
 
@@ -735,7 +735,6 @@ Curl_http_output_auth(struct connectdata *conn,
   return result;
 }
 
-
 /*
  * Curl_http_input_auth() deals with Proxy-Authenticate: and WWW-Authenticate:
  * headers. They are dealt with both in the transfer.c main loop and in the
@@ -748,7 +747,7 @@ CURLcode Curl_http_input_auth(struct connectdata *conn, bool proxy,
   /*
    * This resource requires authentication
    */
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
 
 #ifdef USE_SPNEGO
   struct negotiatedata *negdata = proxy?
@@ -780,7 +779,6 @@ CURLcode Curl_http_input_auth(struct connectdata *conn, bool proxy,
    * request is sent, and then it is again set _after_ all response 401/407
    * headers have been received but then only to a single preferred method
    * (bit).
-   *
    */
 
   while(*auth) {
@@ -893,6 +891,7 @@ CURLcode Curl_http_input_auth(struct connectdata *conn, bool proxy,
     while(*auth && ISSPACE(*auth))
       auth++;
   }
+
   return CURLE_OK;
 }
 
@@ -908,7 +907,7 @@ CURLcode Curl_http_input_auth(struct connectdata *conn, bool proxy,
  */
 static int http_should_fail(struct connectdata *conn)
 {
-  struct SessionHandle *data;
+  struct Curl_easy *data;
   int httpcode;
 
   DEBUGASSERT(conn);
@@ -934,8 +933,7 @@ static int http_should_fail(struct connectdata *conn)
   ** Any code >= 400 that's not 401 or 407 is always
   ** a terminal error
   */
-  if((httpcode != 401) &&
-      (httpcode != 407))
+  if((httpcode != 401) && (httpcode != 407))
     return 1;
 
   /*
@@ -986,7 +984,7 @@ static size_t readmoredata(char *buffer,
   struct HTTP *http = conn->data->req.protop;
   size_t fullsize = size * nitems;
 
-  if(0 == http->postsize)
+  if(!http->postsize)
     /* nothing to return */
     return 0;
 
@@ -1001,8 +999,8 @@ static size_t readmoredata(char *buffer,
       /* move backup data into focus and continue on that */
       http->postdata = http->backup.postdata;
       http->postsize = http->backup.postsize;
-      conn->data->set.fread_func = http->backup.fread_func;
-      conn->data->set.in = http->backup.fread_in;
+      conn->data->state.fread_func = http->backup.fread_func;
+      conn->data->state.in = http->backup.fread_in;
 
       http->sending++; /* move one step up */
 
@@ -1092,15 +1090,14 @@ CURLcode Curl_add_buffer_send(Curl_send_buffer *in,
     return result;
   }
 
-
-  if(conn->handler->flags & PROTOPT_SSL) {
+  if((conn->handler->flags & PROTOPT_SSL) && conn->httpversion != 20) {
     /* We never send more than CURL_MAX_WRITE_SIZE bytes in one single chunk
        when we speak HTTPS, as if only a fraction of it is sent now, this data
        needs to fit into the normal read-callback buffer later on and that
        buffer is using this size.
     */
 
-    sendsize= (size > CURL_MAX_WRITE_SIZE)?CURL_MAX_WRITE_SIZE:size;
+    sendsize = (size > CURL_MAX_WRITE_SIZE) ? CURL_MAX_WRITE_SIZE : size;
 
     /* OpenSSL is very picky and we must send the SAME buffer pointer to the
        library when we attempt to re-send this buffer. Sending the same data
@@ -1123,7 +1120,7 @@ CURLcode Curl_add_buffer_send(Curl_send_buffer *in,
      * only send away a part).
      */
     /* how much of the header that was sent */
-    size_t headlen = (size_t)amount>headersize?headersize:(size_t)amount;
+    size_t headlen = (size_t)amount>headersize ? headersize : (size_t)amount;
     size_t bodylen = amount - headlen;
 
     if(conn->data->set.verbose) {
@@ -1136,17 +1133,17 @@ CURLcode Curl_add_buffer_send(Curl_send_buffer *in,
                    ptr+headlen, bodylen, conn);
       }
     }
-    if(bodylen)
-      /* since we sent a piece of the body here, up the byte counter for it
-         accordingly */
-      http->writebytecount += bodylen;
 
     /* 'amount' can never be a very large value here so typecasting it so a
        signed 31 bit value should not cause problems even if ssize_t is
        64bit */
     *bytes_written += (long)amount;
 
     if(http) {
+      /* if we sent a piece of the body here, up the byte counter for it
+         accordingly */
+      http->writebytecount += bodylen;
+
       if((size_t)amount != size) {
         /* The whole request could not be sent in one system call. We must
            queue it up and send it later when we get the chance. We must not
@@ -1157,14 +1154,14 @@ CURLcode Curl_add_buffer_send(Curl_send_buffer *in,
         ptr = in->buffer + amount;
 
         /* backup the currently set pointers */
-        http->backup.fread_func = conn->data->set.fread_func;
-        http->backup.fread_in = conn->data->set.in;
+        http->backup.fread_func = conn->data->state.fread_func;
+        http->backup.fread_in = conn->data->state.in;
         http->backup.postdata = http->postdata;
         http->backup.postsize = http->postsize;
 
         /* set the new pointers for the request-sending */
-        conn->data->set.fread_func = (curl_read_callback)readmoredata;
-        conn->data->set.in = (void *)conn;
+        conn->data->state.fread_func = (curl_read_callback)readmoredata;
+        conn->data->state.in = (void *)conn;
         http->postdata = ptr;
         http->postsize = (curl_off_t)size;
 
@@ -1242,11 +1239,11 @@ CURLcode Curl_add_buffer(Curl_send_buffer *in, const void *inptr, size_t size)
        buffer size that doubles the required size. If this new size
        would wrap size_t, then just use the largest possible one */
 
-    if((size > (size_t)-1/2) || (in->size_used > (size_t)-1/2) ||
-       (~(size*2) < (in->size_used*2)))
+    if((size > (size_t)-1 / 2) || (in->size_used > (size_t)-1 / 2) ||
+       (~(size * 2) < (in->size_used * 2)))
       new_size = (size_t)-1;
     else
-      new_size = (in->size_used+size)*2;
+      new_size = (in->size_used+size) * 2;
 
     if(in->buffer)
       /* we have a buffer, enlarge the existing one */
@@ -1394,7 +1391,8 @@ static CURLcode https_connecting(struct connectdata *conn, bool *done)
 #endif
 
 #if defined(USE_OPENSSL) || defined(USE_GNUTLS) || defined(USE_SCHANNEL) || \
-    defined(USE_DARWINSSL) || defined(USE_POLARSSL) || defined(USE_NSS)
+    defined(USE_DARWINSSL) || defined(USE_POLARSSL) || defined(USE_NSS) || \
+    defined(USE_MBEDTLS)
 /* This function is for OpenSSL, GnuTLS, darwinssl, schannel and polarssl only.
    It should be made to query the generic SSL layer instead. */
 static int https_getsock(struct connectdata *conn,
@@ -1418,6 +1416,7 @@ static int https_getsock(struct connectdata *conn,
       return GETSOCK_READSOCK(0);
     }
   }
+
   return CURLE_OK;
 }
 #else
@@ -1435,14 +1434,14 @@ static int https_getsock(struct connectdata *conn,
 #endif /* USE_OPENSSL || USE_GNUTLS || USE_SCHANNEL */
 
 /*
- * Curl_http_done() gets called from Curl_done() after a single HTTP request
- * has been performed.
+ * Curl_http_done() gets called after a single HTTP request has been
+ * performed.
  */
 
 CURLcode Curl_http_done(struct connectdata *conn,
                         CURLcode status, bool premature)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct HTTP *http = data->req.protop;
 #ifdef USE_NGHTTP2
   struct http_conn *httpc = &conn->proto.httpc;
@@ -1455,8 +1454,10 @@ CURLcode Curl_http_done(struct connectdata *conn,
      data->state.negotiate.state == GSS_AUTHSENT) {
     /* add forbid re-use if http-code != 401/407 as a WA only needed for
      * 401/407 that signal auth failure (empty) otherwise state will be RECV
-     * with current code */
-    if((data->req.httpcode != 401) && (data->req.httpcode != 407))
+     * with current code.
+     * Do not close CONNECT_ONLY connections. */
+    if((data->req.httpcode != 401) && (data->req.httpcode != 407) &&
+       !data->set.connect_only)
       connclose(conn, "Negotiate transfer completed");
     Curl_cleanup_negotiate(data);
   }
@@ -1466,7 +1467,7 @@ CURLcode Curl_http_done(struct connectdata *conn,
   conn->seek_func = data->set.seek_func; /* restore */
   conn->seek_client = data->set.seek_client; /* restore */
 
-  if(http == NULL)
+  if(!http)
     return CURLE_OK;
 
   if(http->send_buffer) {
@@ -1479,11 +1480,16 @@ CURLcode Curl_http_done(struct connectdata *conn,
     DEBUGF(infof(data, "free header_recvbuf!!\n"));
     Curl_add_buffer_free(http->header_recvbuf);
     http->header_recvbuf = NULL; /* clear the pointer */
-    for(; http->push_headers_used > 0; --http->push_headers_used) {
-      free(http->push_headers[http->push_headers_used - 1]);
+    Curl_add_buffer_free(http->trailer_recvbuf);
+    http->trailer_recvbuf = NULL; /* clear the pointer */
+    if(http->push_headers) {
+      /* if they weren't used and then freed before */
+      for(; http->push_headers_used > 0; --http->push_headers_used) {
+        free(http->push_headers[http->push_headers_used - 1]);
+      }
+      free(http->push_headers);
+      http->push_headers = NULL;
     }
-    free(http->push_headers);
-    http->push_headers = NULL;
   }
   if(http->stream_id) {
     nghttp2_session_set_stream_user_data(httpc->h2, http->stream_id, 0);
@@ -1511,9 +1517,9 @@ CURLcode Curl_http_done(struct connectdata *conn,
                       entire operation is complete */
      !conn->bits.retry &&
      !data->set.connect_only &&
-     ((http->readbytecount +
-       data->req.headerbytecount -
-       data->req.deductheadercount)) <= 0) {
+     (http->readbytecount +
+      data->req.headerbytecount -
+      data->req.deductheadercount) <= 0) {
     /* If this connection isn't simply closed to be retried, AND nothing was
        read from the HTTP server (that counts), this can't be right so we
        return an error here */
@@ -1524,7 +1530,6 @@ CURLcode Curl_http_done(struct connectdata *conn,
   return CURLE_OK;
 }
 
-
 /*
  * Determine if we should use HTTP 1.1 (OR BETTER) for this request. Reasons
  * to avoid it include:
@@ -1534,18 +1539,20 @@ CURLcode Curl_http_done(struct connectdata *conn,
  * - if any server previously contacted to handle this request only supports
  * 1.0.
  */
-static bool use_http_1_1plus(const struct SessionHandle *data,
+static bool use_http_1_1plus(const struct Curl_easy *data,
                              const struct connectdata *conn)
 {
-  return ((data->set.httpversion >= CURL_HTTP_VERSION_1_1) ||
-         ((data->set.httpversion != CURL_HTTP_VERSION_1_0) &&
-          ((conn->httpversion == 11) ||
-           ((conn->httpversion != 10) &&
-            (data->state.httpversion != 10))))) ? TRUE : FALSE;
+  if((data->state.httpversion == 10) || (conn->httpversion == 10))
+    return FALSE;
+  if((data->set.httpversion == CURL_HTTP_VERSION_1_0) &&
+     (conn->httpversion <= 10))
+    return FALSE;
+  return ((data->set.httpversion == CURL_HTTP_VERSION_NONE) ||
+          (data->set.httpversion >= CURL_HTTP_VERSION_1_1));
 }
 
 /* check and possibly add an Expect: header */
-static CURLcode expect100(struct SessionHandle *data,
+static CURLcode expect100(struct Curl_easy *data,
                           struct connectdata *conn,
                           Curl_send_buffer *req_buffer)
 {
@@ -1570,6 +1577,7 @@ static CURLcode expect100(struct SessionHandle *data,
         data->state.expect100header = TRUE;
     }
   }
+
   return result;
 }
 
@@ -1587,7 +1595,7 @@ CURLcode Curl_add_custom_headers(struct connectdata *conn,
   struct curl_slist *h[2];
   struct curl_slist *headers;
   int numlists=1; /* by default */
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   int i;
 
   enum proxy_use proxy;
@@ -1688,16 +1696,23 @@ CURLcode Curl_add_custom_headers(struct connectdata *conn,
       headers = headers->next;
     }
   }
+
   return CURLE_OK;
 }
 
-CURLcode Curl_add_timecondition(struct SessionHandle *data,
+CURLcode Curl_add_timecondition(struct Curl_easy *data,
                                 Curl_send_buffer *req_buffer)
 {
   const struct tm *tm;
   char *buf = data->state.buffer;
   struct tm keeptime;
-  CURLcode result = Curl_gmtime(data->set.timevalue, &keeptime);
+  CURLcode result;
+
+  if(data->set.timecondition == CURL_TIMECOND_NONE)
+    /* no condition was asked for */
+    return CURLE_OK;
+
+  result = Curl_gmtime(data->set.timevalue, &keeptime);
   if(result) {
     failf(data, "Invalid TIMEVALUE");
     return result;
@@ -1723,8 +1738,9 @@ CURLcode Curl_add_timecondition(struct SessionHandle *data,
            tm->tm_sec);
 
   switch(data->set.timecondition) {
-  case CURL_TIMECOND_IFMODSINCE:
   default:
+    break;
+  case CURL_TIMECOND_IFMODSINCE:
     result = Curl_add_bufferf(req_buffer,
                               "If-Modified-Since: %s\r\n", buf);
     break;
@@ -1742,13 +1758,13 @@ CURLcode Curl_add_timecondition(struct SessionHandle *data,
 }
 
 /*
- * Curl_http() gets called from the generic Curl_do() function when a HTTP
+ * Curl_http() gets called from the generic multi_do() function when a HTTP
  * request is to be performed. This creates and sends a properly constructed
  * HTTP request.
  */
 CURLcode Curl_http(struct connectdata *conn, bool *done)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   CURLcode result = CURLE_OK;
   struct HTTP *http;
   const char *ppath = data->state.path;
@@ -1776,15 +1792,8 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
   if(conn->httpversion < 20) { /* unless the connection is re-used and already
                                   http2 */
     switch(conn->negnpn) {
-    case CURL_HTTP_VERSION_2_0:
+    case CURL_HTTP_VERSION_2:
       conn->httpversion = 20; /* we know we're on HTTP/2 now */
-      result = Curl_http2_init(conn);
-      if(result)
-        return result;
-
-      result = Curl_http2_setup(conn);
-      if(result)
-        return result;
 
       result = Curl_http2_switched(conn, NULL, 0);
       if(result)
@@ -1794,7 +1803,18 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
       /* continue with HTTP/1.1 when explicitly requested */
       break;
     default:
-      /* and as fallback */
+      /* Check if user wants to use HTTP/2 with clear TCP*/
+#ifdef USE_NGHTTP2
+      if(conn->data->set.httpversion ==
+         CURL_HTTP_VERSION_2_PRIOR_KNOWLEDGE) {
+        DEBUGF(infof(data, "HTTP/2 over clean TCP\n"));
+        conn->httpversion = 20;
+
+        result = Curl_http2_switched(conn, NULL, 0);
+        if(result)
+          return result;
+      }
+#endif
       break;
     }
   }
@@ -1814,6 +1834,8 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
     data->state.first_host = strdup(conn->host.name);
     if(!data->state.first_host)
       return CURLE_OUT_OF_MEMORY;
+
+    data->state.first_remote_port = conn->remote_port;
   }
   http->writebytecount = http->readbytecount = 0;
 
@@ -1895,6 +1917,10 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
     if(!conn->allocptr.accept_encoding)
       return CURLE_OUT_OF_MEMORY;
   }
+  else {
+    Curl_safefree(conn->allocptr.accept_encoding);
+    conn->allocptr.accept_encoding = NULL;
+  }
 
 #ifdef HAVE_LIBZ
   /* we only consider transfer-encoding magic if libz support is built-in */
@@ -2130,7 +2156,7 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
      * file size before we continue this venture in the dark lands of HTTP.
      *********************************************************************/
 
-    if(data->state.resume_from < 0 ) {
+    if(data->state.resume_from < 0) {
       /*
        * This is meant to get the size of the present remote-file by itself.
        * We don't support this now. Bail out!
@@ -2162,8 +2188,8 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
               BUFSIZE : curlx_sotouz(data->state.resume_from - passed);
 
             size_t actuallyread =
-              data->set.fread_func(data->state.buffer, 1, readthisamountnow,
-                                   data->set.in);
+              data->state.fread_func(data->state.buffer, 1, readthisamountnow,
+                                     data->state.in);
 
             passed += actuallyread;
             if((actuallyread == 0) || (actuallyread > readthisamountnow)) {
@@ -2279,7 +2305,6 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
                      "%s" /* TE: */
                      "%s" /* accept-encoding */
                      "%s" /* referer */
-                     "%s" /* Proxy-Connection */
                      "%s",/* transfer-encoding */
 
                      ftp_typecode,
@@ -2302,10 +2327,6 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
                      conn->allocptr.accept_encoding:"",
                      (data->change.referer && conn->allocptr.ref)?
                      conn->allocptr.ref:"" /* Referer: <data> */,
-                     (conn->bits.httpproxy &&
-                      !conn->bits.tunnel_proxy &&
-                      !Curl_checkProxyheaders(conn, "Proxy-Connection:"))?
-                     "Proxy-Connection: Keep-Alive\r\n":"",
                      te
       );
 
@@ -2329,7 +2350,7 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
 
   if(!(conn->handler->flags&PROTOPT_SSL) &&
      conn->httpversion != 20 &&
-     (data->set.httpversion == CURL_HTTP_VERSION_2_0)) {
+     (data->set.httpversion == CURL_HTTP_VERSION_2)) {
     /* append HTTP2 upgrade magic stuff to the HTTP request if it isn't done
        over SSL */
     result = Curl_http2_request_upgrade(req_buffer, conn);
@@ -2390,11 +2411,9 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
   }
 #endif
 
-  if(data->set.timecondition) {
-    result = Curl_add_timecondition(data, req_buffer);
-    if(result)
-      return result;
-  }
+  result = Curl_add_timecondition(data, req_buffer);
+  if(result)
+    return result;
 
   result = Curl_add_custom_headers(conn, FALSE, req_buffer);
   if(result)
@@ -2437,11 +2456,11 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
        on. The data->set.fread_func pointer itself will be changed for the
        multipart case to the function that returns a multipart formatted
        stream. */
-    http->form.fread_func = data->set.fread_func;
+    http->form.fread_func = data->state.fread_func;
 
     /* Set the read function to read from the generated form data */
-    data->set.fread_func = (curl_read_callback)Curl_FormReader;
-    data->set.in = &http->form;
+    data->state.fread_func = (curl_read_callback)Curl_FormReader;
+    data->state.in = &http->form;
 
     http->sending = HTTPSEND_BODY;
 
@@ -2659,8 +2678,8 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
 
         http->sending = HTTPSEND_BODY;
 
-        data->set.fread_func = (curl_read_callback)readmoredata;
-        data->set.in = (void *)conn;
+        data->state.fread_func = (curl_read_callback)readmoredata;
+        data->state.in = (void *)conn;
 
         /* set the upload size to the progress meter */
         Curl_pgrsSetUploadSize(data, http->postsize);
@@ -2758,7 +2777,7 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
  * Returns TRUE if member of the list matches prefix of string
  */
 static bool
-checkhttpprefix(struct SessionHandle *data,
+checkhttpprefix(struct Curl_easy *data,
                 const char *s)
 {
   struct curl_slist *head = data->set.http200aliases;
@@ -2797,7 +2816,7 @@ checkhttpprefix(struct SessionHandle *data,
 
 #ifndef CURL_DISABLE_RTSP
 static bool
-checkrtspprefix(struct SessionHandle *data,
+checkrtspprefix(struct Curl_easy *data,
                 const char *s)
 {
 
@@ -2825,7 +2844,7 @@ checkrtspprefix(struct SessionHandle *data,
 #endif /* CURL_DISABLE_RTSP */
 
 static bool
-checkprotoprefix(struct SessionHandle *data, struct connectdata *conn,
+checkprotoprefix(struct Curl_easy *data, struct connectdata *conn,
                  const char *s)
 {
 #ifndef CURL_DISABLE_RTSP
@@ -2843,7 +2862,7 @@ checkprotoprefix(struct SessionHandle *data, struct connectdata *conn,
  * header. We make sure that the full string fit in the allocated header
  * buffer, or else we enlarge it.
  */
-static CURLcode header_append(struct SessionHandle *data,
+static CURLcode header_append(struct Curl_easy *data,
                               struct SingleRequest *k,
                               size_t length)
 {
@@ -2881,7 +2900,7 @@ static CURLcode header_append(struct SessionHandle *data,
   return CURLE_OK;
 }
 
-static void print_http_error(struct SessionHandle *data)
+static void print_http_error(struct Curl_easy *data)
 {
   struct SingleRequest *k = &data->req;
   char *beg = k->p;
@@ -2921,7 +2940,7 @@ static void print_http_error(struct SessionHandle *data)
 /*
  * Read any HTTP header lines from the server and pass them to the client app.
  */
-CURLcode Curl_http_readwrite_headers(struct SessionHandle *data,
+CURLcode Curl_http_readwrite_headers(struct Curl_easy *data,
                                        struct connectdata *conn,
                                        ssize_t *nread,
                                        bool *stop_reading)
@@ -3035,7 +3054,7 @@ CURLcode Curl_http_readwrite_headers(struct SessionHandle *data,
         switch(k->httpcode) {
         case 100:
           /* if we did wait for this do enable write now! */
-          if(k->exp100) {
+          if(k->exp100 > EXP100_SEND_DATA) {
             k->exp100 = EXP100_SEND_DATA;
             k->keepon |= KEEP_SEND;
           }
@@ -3119,52 +3138,50 @@ CURLcode Curl_http_readwrite_headers(struct SessionHandle *data,
       data->req.deductheadercount =
         (100 <= k->httpcode && 199 >= k->httpcode)?data->req.headerbytecount:0;
 
-      if(!*stop_reading) {
-        /* Curl_http_auth_act() checks what authentication methods
-         * that are available and decides which one (if any) to
-         * use. It will set 'newurl' if an auth method was picked. */
-        result = Curl_http_auth_act(conn);
+      /* Curl_http_auth_act() checks what authentication methods
+       * that are available and decides which one (if any) to
+       * use. It will set 'newurl' if an auth method was picked. */
+      result = Curl_http_auth_act(conn);
 
-        if(result)
-          return result;
+      if(result)
+        return result;
 
-        if(k->httpcode >= 300) {
-          if((!conn->bits.authneg) && !conn->bits.close &&
-             !conn->bits.rewindaftersend) {
-            /*
-             * General treatment of errors when about to send data. Including :
-             * "417 Expectation Failed", while waiting for 100-continue.
-             *
-             * The check for close above is done simply because of something
-             * else has already deemed the connection to get closed then
-             * something else should've considered the big picture and we
-             * avoid this check.
-             *
-             * rewindaftersend indicates that something has told libcurl to
-             * continue sending even if it gets discarded
+      if(k->httpcode >= 300) {
+        if((!conn->bits.authneg) && !conn->bits.close &&
+           !conn->bits.rewindaftersend) {
+          /*
+           * General treatment of errors when about to send data. Including :
+           * "417 Expectation Failed", while waiting for 100-continue.
+           *
+           * The check for close above is done simply because of something
+           * else has already deemed the connection to get closed then
+           * something else should've considered the big picture and we
+           * avoid this check.
+           *
+           * rewindaftersend indicates that something has told libcurl to
+           * continue sending even if it gets discarded
+           */
+
+          switch(data->set.httpreq) {
+          case HTTPREQ_PUT:
+          case HTTPREQ_POST:
+          case HTTPREQ_POST_FORM:
+            /* We got an error response. If this happened before the whole
+             * request body has been sent we stop sending and mark the
+             * connection for closure after we've read the entire response.
              */
-
-            switch(data->set.httpreq) {
-            case HTTPREQ_PUT:
-            case HTTPREQ_POST:
-            case HTTPREQ_POST_FORM:
-              /* We got an error response. If this happened before the whole
-               * request body has been sent we stop sending and mark the
-               * connection for closure after we've read the entire response.
-               */
-              if(!k->upload_done) {
-                infof(data, "HTTP error before end of send, stop sending\n");
-                connclose(conn, "Stop sending data before everything sent");
-                k->upload_done = TRUE;
-                k->keepon &= ~KEEP_SEND; /* don't send */
-                if(data->state.expect100header)
-                  k->exp100 = EXP100_FAILED;
-              }
-              break;
-
-            default: /* default label present to avoid compiler warnings */
-              break;
+            if(!k->upload_done) {
+              infof(data, "HTTP error before end of send, stop sending\n");
+              connclose(conn, "Stop sending data before everything sent");
+              k->upload_done = TRUE;
+              k->keepon &= ~KEEP_SEND; /* don't send */
+              if(data->state.expect100header)
+                k->exp100 = EXP100_FAILED;
             }
+            break;
+
+          default: /* default label present to avoid compiler warnings */
+            break;
           }
         }
 
@@ -3185,6 +3202,16 @@ CURLcode Curl_http_readwrite_headers(struct SessionHandle *data,
          */
         if(data->set.opt_no_body)
           *stop_reading = TRUE;
+#ifndef CURL_DISABLE_RTSP
+        else if((conn->handler->protocol & CURLPROTO_RTSP) &&
+                (data->set.rtspreq == RTSPREQ_DESCRIBE) &&
+                (k->size <= -1))
+          /* Respect section 4.4 of rfc2326: If the Content-Length header is
+             absent, a length 0 must be assumed.  It will prevent libcurl from
+             hanging on DESCRIBE request that got refused for whatever
+             reason */
+          *stop_reading = TRUE;
+#endif
         else {
           /* If we know the expected size of this document, we set the
              maximum download size to the size of the expected
@@ -3279,6 +3306,13 @@ CURLcode Curl_http_readwrite_headers(struct SessionHandle *data,
                     &httpversion_major,
                     &conn->httpversion,
                     &k->httpcode);
+
+        if(nc == 1 && httpversion_major == 2 &&
+           1 == sscanf(HEADER1, " HTTP/2 %d", &k->httpcode)) {
+          conn->httpversion = 0;
+          nc = 3;
+        }
+
         if(nc==3) {
           conn->httpversion += 10 * httpversion_major;
 
@@ -3576,8 +3610,7 @@ CURLcode Curl_http_readwrite_headers(struct SessionHandle *data,
 
     }
     else if(checkprefix("Content-Encoding:", k->p) &&
-            (data->set.str[STRING_ENCODING] ||
-             conn->httpversion == 20)) {
+            data->set.str[STRING_ENCODING]) {
       /*
        * Process Content-Encoding. Look for the values: identity,
        * gzip, deflate, compress, x-gzip and x-compress. x-gzip and
@@ -3726,7 +3759,7 @@ CURLcode Curl_http_readwrite_headers(struct SessionHandle *data,
     k->hbufp = data->state.headerbuff;
     k->hbuflen = 0;
   }
-  while(!*stop_reading && *k->str); /* header line within buffer */
+  while(*k->str); /* header line within buffer */
 
   /* We might have reached the end of the header part here, but
      there might be a non-header part left in the end of the read