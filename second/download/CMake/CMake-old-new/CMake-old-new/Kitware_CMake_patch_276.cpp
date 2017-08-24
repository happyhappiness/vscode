@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -63,7 +63,6 @@
 #include "share.h"
 #include "hostip.h"
 #include "http.h"
-#include "curl_memory.h"
 #include "select.h"
 #include "parsedate.h" /* for the week day and month names */
 #include "strtoofft.h"
@@ -73,15 +72,14 @@
 #include "http_proxy.h"
 #include "warnless.h"
 #include "non-ascii.h"
-#include "bundles.h"
+#include "conncache.h"
 #include "pipeline.h"
 #include "http2.h"
 #include "connect.h"
+#include "curl_printf.h"
 
-#define _MPRINTF_REPLACE /* use our functions only */
-#include <curl/mprintf.h>
-
-/* The last #include file should be: */
+/* The last #include files should be: */
+#include "curl_memory.h"
 #include "memdebug.h"
 
 /*
@@ -155,12 +153,18 @@ CURLcode Curl_http_setup_conn(struct connectdata *conn)
 {
   /* allocate the HTTP-specific struct for the SessionHandle, only to survive
      during this request */
+  struct HTTP *http;
   DEBUGASSERT(conn->data->req.protop == NULL);
 
-  conn->data->req.protop = calloc(1, sizeof(struct HTTP));
-  if(!conn->data->req.protop)
+  http = calloc(1, sizeof(struct HTTP));
+  if(!http)
     return CURLE_OUT_OF_MEMORY;
 
+  conn->data->req.protop = http;
+
+  Curl_http2_setup_conn(conn);
+  Curl_http2_setup_req(conn->data);
+
   return CURLE_OK;
 }
 
@@ -279,7 +283,7 @@ static CURLcode http_output_basic(struct connectdata *conn, bool proxy)
   char **userp;
   const char *user;
   const char *pwd;
-  CURLcode error;
+  CURLcode result;
 
   if(proxy) {
     userp = &conn->allocptr.proxyuserpwd;
@@ -294,16 +298,16 @@ static CURLcode http_output_basic(struct connectdata *conn, bool proxy)
 
   snprintf(data->state.buffer, sizeof(data->state.buffer), "%s:%s", user, pwd);
 
-  error = Curl_base64_encode(data,
-                             data->state.buffer, strlen(data->state.buffer),
-                             &authorization, &size);
-  if(error)
-    return error;
+  result = Curl_base64_encode(data,
+                              data->state.buffer, strlen(data->state.buffer),
+                              &authorization, &size);
+  if(result)
+    return result;
 
   if(!authorization)
     return CURLE_REMOTE_ACCESS_DENIED;
 
-  Curl_safefree(*userp);
+  free(*userp);
   *userp = aprintf("%sAuthorization: Basic %s\r\n",
                    proxy?"Proxy-":"",
                    authorization);
@@ -392,16 +396,21 @@ static CURLcode http_perhapsrewind(struct connectdata *conn)
 
   bytessent = http->writebytecount;
 
-  if(conn->bits.authneg)
+  if(conn->bits.authneg) {
     /* This is a state where we are known to be negotiating and we don't send
        any data then. */
     expectsend = 0;
+  }
+  else if(!conn->bits.protoconnstart) {
+    /* HTTP CONNECT in progress: there is no body */
+    expectsend = 0;
+  }
   else {
     /* figure out how much data we are expected to send */
     switch(data->set.httpreq) {
     case HTTPREQ_POST:
-      if(data->set.postfieldsize != -1)
-        expectsend = data->set.postfieldsize;
+      if(data->state.infilesize != -1)
+        expectsend = data->state.infilesize;
       else if(data->set.postfields)
         expectsend = (curl_off_t)strlen(data->set.postfields);
       break;
@@ -420,6 +429,7 @@ static CURLcode http_perhapsrewind(struct connectdata *conn)
   conn->bits.rewindaftersend = FALSE; /* default */
 
   if((expectsend == -1) || (expectsend > bytessent)) {
+#if defined(USE_NTLM)
     /* There is still data left to send */
     if((data->state.authproxy.picked == CURLAUTH_NTLM) ||
        (data->state.authhost.picked == CURLAUTH_NTLM) ||
@@ -439,6 +449,7 @@ static CURLcode http_perhapsrewind(struct connectdata *conn)
 
         return CURLE_OK;
       }
+
       if(conn->bits.close)
         /* this is already marked to get closed */
         return CURLE_OK;
@@ -447,9 +458,9 @@ static CURLcode http_perhapsrewind(struct connectdata *conn)
             CURL_FORMAT_CURL_OFF_T " bytes\n",
             (curl_off_t)(expectsend - bytessent));
     }
+#endif
 
-    /* This is not NTLM or many bytes left to send: close
-     */
+    /* This is not NTLM or many bytes left to send: close */
     connclose(conn, "Mid-auth HTTP and much data left to send");
     data->req.size = 0; /* don't download any more than 0 bytes */
 
@@ -476,7 +487,7 @@ CURLcode Curl_http_auth_act(struct connectdata *conn)
   struct SessionHandle *data = conn->data;
   bool pickhost = FALSE;
   bool pickproxy = FALSE;
-  CURLcode code = CURLE_OK;
+  CURLcode result = CURLE_OK;
 
   if(100 <= data->req.httpcode && 199 >= data->req.httpcode)
     /* this is a transient response code, ignore */
@@ -512,9 +523,9 @@ CURLcode Curl_http_auth_act(struct connectdata *conn)
     if((data->set.httpreq != HTTPREQ_GET) &&
        (data->set.httpreq != HTTPREQ_HEAD) &&
        !conn->bits.rewindaftersend) {
-      code = http_perhapsrewind(conn);
-      if(code)
-        return code;
+      result = http_perhapsrewind(conn);
+      if(result)
+        return result;
     }
   }
 
@@ -536,10 +547,10 @@ CURLcode Curl_http_auth_act(struct connectdata *conn)
   if(http_should_fail(conn)) {
     failf (data, "The requested URL returned error: %d",
            data->req.httpcode);
-    code = CURLE_HTTP_RETURNED_ERROR;
+    result = CURLE_HTTP_RETURNED_ERROR;
   }
 
-  return code;
+  return result;
 }
 
 
@@ -554,9 +565,11 @@ output_auth_headers(struct connectdata *conn,
                     const char *path,
                     bool proxy)
 {
-  struct SessionHandle *data = conn->data;
-  const char *auth=NULL;
+  const char *auth = NULL;
   CURLcode result = CURLE_OK;
+#if defined(USE_SPNEGO) || !defined(CURL_DISABLE_VERBOSE_STRINGS)
+  struct SessionHandle *data = conn->data;
+#endif
 #ifdef USE_SPNEGO
   struct negotiatedata *negdata = proxy?
     &data->state.proxyneg:&data->state.negotiate;
@@ -672,7 +685,7 @@ Curl_http_output_auth(struct connectdata *conn,
 
   if((conn->bits.httpproxy && conn->bits.proxy_user_passwd) ||
      conn->bits.user_passwd)
-    /* continue please */ ;
+    /* continue please */;
   else {
     authhost->done = TRUE;
     authproxy->done = TRUE;
@@ -773,14 +786,13 @@ CURLcode Curl_http_input_auth(struct connectdata *conn, bool proxy,
   while(*auth) {
 #ifdef USE_SPNEGO
     if(checkprefix("Negotiate", auth)) {
-      int neg;
       *availp |= CURLAUTH_NEGOTIATE;
       authp->avail |= CURLAUTH_NEGOTIATE;
 
       if(authp->picked == CURLAUTH_NEGOTIATE) {
         if(negdata->state == GSS_AUTHSENT || negdata->state == GSS_AUTHNONE) {
-          neg = Curl_input_negotiate(conn, proxy, auth);
-          if(neg == 0) {
+          CURLcode result = Curl_input_negotiate(conn, proxy, auth);
+          if(!result) {
             DEBUGASSERT(!data->req.newurl);
             data->req.newurl = strdup(data->change.url);
             if(!data->req.newurl)
@@ -804,9 +816,8 @@ CURLcode Curl_http_input_auth(struct connectdata *conn, bool proxy,
         if(authp->picked == CURLAUTH_NTLM ||
            authp->picked == CURLAUTH_NTLM_WB) {
           /* NTLM authentication is picked and activated */
-          CURLcode ntlm =
-            Curl_input_ntlm(conn, proxy, auth);
-          if(CURLE_OK == ntlm) {
+          CURLcode result = Curl_input_ntlm(conn, proxy, auth);
+          if(!result) {
             data->state.authproblem = FALSE;
 #ifdef NTLM_WB_ENABLED
             if(authp->picked == CURLAUTH_NTLM_WB) {
@@ -844,17 +855,16 @@ CURLcode Curl_http_input_auth(struct connectdata *conn, bool proxy,
             infof(data, "Ignoring duplicate digest auth header.\n");
           }
           else {
-            CURLdigest dig;
+            CURLcode result;
             *availp |= CURLAUTH_DIGEST;
             authp->avail |= CURLAUTH_DIGEST;
 
             /* We call this function on input Digest headers even if Digest
              * authentication isn't activated yet, as we need to store the
              * incoming data from this header in case we are gonna use
              * Digest. */
-            dig = Curl_input_digest(conn, proxy, auth);
-
-            if(CURLDIGEST_FINE != dig) {
+            result = Curl_input_digest(conn, proxy, auth);
+            if(result) {
               infof(data, "Authentication problem. Ignoring this.\n");
               data->state.authproblem = TRUE;
             }
@@ -991,8 +1001,8 @@ static size_t readmoredata(char *buffer,
       /* move backup data into focus and continue on that */
       http->postdata = http->backup.postdata;
       http->postsize = http->backup.postsize;
-      conn->fread_func = http->backup.fread_func;
-      conn->fread_in = http->backup.fread_in;
+      conn->data->set.fread_func = http->backup.fread_func;
+      conn->data->set.in = http->backup.fread_in;
 
       http->sending++; /* move one step up */
 
@@ -1023,6 +1033,16 @@ Curl_send_buffer *Curl_add_buffer_init(void)
 }
 
 /*
+ * Curl_add_buffer_free() frees all associated resources.
+ */
+void Curl_add_buffer_free(Curl_send_buffer *buff)
+{
+  if(buff) /* deal with NULL input */
+    free(buff->buffer);
+  free(buff);
+}
+
+/*
  * Curl_add_buffer_send() sends a header buffer and frees all associated
  * memory.  Body data may be appended to the header data if desired.
  *
@@ -1041,7 +1061,7 @@ CURLcode Curl_add_buffer_send(Curl_send_buffer *in,
 
 {
   ssize_t amount;
-  CURLcode res;
+  CURLcode result;
   char *ptr;
   size_t size;
   struct HTTP *http = conn->data->req.protop;
@@ -1064,14 +1084,12 @@ CURLcode Curl_add_buffer_send(Curl_send_buffer *in,
 
   DEBUGASSERT(size > included_body_bytes);
 
-  res = Curl_convert_to_network(conn->data, ptr, headersize);
+  result = Curl_convert_to_network(conn->data, ptr, headersize);
   /* Curl_convert_to_network calls failf if unsuccessful */
-  if(res) {
+  if(result) {
     /* conversion failed, free memory and return to the caller */
-    if(in->buffer)
-      free(in->buffer);
-    free(in);
-    return res;
+    Curl_add_buffer_free(in);
+    return result;
   }
 
 
@@ -1096,9 +1114,9 @@ CURLcode Curl_add_buffer_send(Curl_send_buffer *in,
   else
     sendsize = size;
 
-  res = Curl_write(conn, sockfd, ptr, sendsize, &amount);
+  result = Curl_write(conn, sockfd, ptr, sendsize, &amount);
 
-  if(CURLE_OK == res) {
+  if(!result) {
     /*
      * Note that we may not send the entire chunk at once, and we have a set
      * number of data bytes at the end of the big buffer (out of which we may
@@ -1139,14 +1157,14 @@ CURLcode Curl_add_buffer_send(Curl_send_buffer *in,
         ptr = in->buffer + amount;
 
         /* backup the currently set pointers */
-        http->backup.fread_func = conn->fread_func;
-        http->backup.fread_in = conn->fread_in;
+        http->backup.fread_func = conn->data->set.fread_func;
+        http->backup.fread_in = conn->data->set.in;
         http->backup.postdata = http->postdata;
         http->backup.postsize = http->postsize;
 
         /* set the new pointers for the request-sending */
-        conn->fread_func = (curl_read_callback)readmoredata;
-        conn->fread_in = (void *)conn;
+        conn->data->set.fread_func = (curl_read_callback)readmoredata;
+        conn->data->set.in = (void *)conn;
         http->postdata = ptr;
         http->postsize = (curl_off_t)size;
 
@@ -1169,14 +1187,12 @@ CURLcode Curl_add_buffer_send(Curl_send_buffer *in,
         */
         return CURLE_SEND_ERROR;
       else
-        conn->writechannel_inuse = FALSE;
+        Curl_pipeline_leave_write(conn);
     }
   }
-  if(in->buffer)
-    free(in->buffer);
-  free(in);
+  Curl_add_buffer_free(in);
 
-  return res;
+  return result;
 }
 
 
@@ -1197,8 +1213,7 @@ CURLcode Curl_add_bufferf(Curl_send_buffer *in, const char *fmt, ...)
     return result;
   }
   /* If we failed, we cleanup the whole buffer and return error */
-  if(in->buffer)
-    free(in->buffer);
+  free(in->buffer);
   free(in);
   return CURLE_OUT_OF_MEMORY;
 }
@@ -1378,7 +1393,7 @@ static CURLcode https_connecting(struct connectdata *conn, bool *done)
 }
 #endif
 
-#if defined(USE_SSLEAY) || defined(USE_GNUTLS) || defined(USE_SCHANNEL) || \
+#if defined(USE_OPENSSL) || defined(USE_GNUTLS) || defined(USE_SCHANNEL) || \
     defined(USE_DARWINSSL) || defined(USE_POLARSSL) || defined(USE_NSS)
 /* This function is for OpenSSL, GnuTLS, darwinssl, schannel and polarssl only.
    It should be made to query the generic SSL layer instead. */
@@ -1417,7 +1432,7 @@ static int https_getsock(struct connectdata *conn,
   return GETSOCK_BLANK;
 }
 #endif /* USE_SSL */
-#endif /* USE_SSLEAY || USE_GNUTLS || USE_SCHANNEL */
+#endif /* USE_OPENSSL || USE_GNUTLS || USE_SCHANNEL */
 
 /*
  * Curl_http_done() gets called from Curl_done() after a single HTTP request
@@ -1428,33 +1443,54 @@ CURLcode Curl_http_done(struct connectdata *conn,
                         CURLcode status, bool premature)
 {
   struct SessionHandle *data = conn->data;
-  struct HTTP *http =data->req.protop;
+  struct HTTP *http = data->req.protop;
+#ifdef USE_NGHTTP2
+  struct http_conn *httpc = &conn->proto.httpc;
+#endif
 
   Curl_unencode_cleanup(conn);
 
 #ifdef USE_SPNEGO
   if(data->state.proxyneg.state == GSS_AUTHSENT ||
-      data->state.negotiate.state == GSS_AUTHSENT)
+     data->state.negotiate.state == GSS_AUTHSENT) {
+    /* add forbid re-use if http-code != 401/407 as a WA only needed for
+     * 401/407 that signal auth failure (empty) otherwise state will be RECV
+     * with current code */
+    if((data->req.httpcode != 401) && (data->req.httpcode != 407))
+      connclose(conn, "Negotiate transfer completed");
     Curl_cleanup_negotiate(data);
+  }
 #endif
 
   /* set the proper values (possibly modified on POST) */
-  conn->fread_func = data->set.fread_func; /* restore */
-  conn->fread_in = data->set.in; /* restore */
   conn->seek_func = data->set.seek_func; /* restore */
   conn->seek_client = data->set.seek_client; /* restore */
 
   if(http == NULL)
     return CURLE_OK;
 
   if(http->send_buffer) {
-    Curl_send_buffer *buff = http->send_buffer;
-
-    free(buff->buffer);
-    free(buff);
+    Curl_add_buffer_free(http->send_buffer);
     http->send_buffer = NULL; /* clear the pointer */
   }
 
+#ifdef USE_NGHTTP2
+  if(http->header_recvbuf) {
+    DEBUGF(infof(data, "free header_recvbuf!!\n"));
+    Curl_add_buffer_free(http->header_recvbuf);
+    http->header_recvbuf = NULL; /* clear the pointer */
+    for(; http->push_headers_used > 0; --http->push_headers_used) {
+      free(http->push_headers[http->push_headers_used - 1]);
+    }
+    free(http->push_headers);
+    http->push_headers = NULL;
+  }
+  if(http->stream_id) {
+    nghttp2_session_set_stream_user_data(httpc->h2, http->stream_id, 0);
+    http->stream_id = 0;
+  }
+#endif
+
   if(HTTPREQ_POST_FORM == data->set.httpreq) {
     data->req.bytecount = http->readbytecount + http->writebytecount;
 
@@ -1468,8 +1504,8 @@ CURLcode Curl_http_done(struct connectdata *conn,
   else if(HTTPREQ_PUT == data->set.httpreq)
     data->req.bytecount = http->readbytecount + http->writebytecount;
 
-  if(status != CURLE_OK)
-    return (status);
+  if(status)
+    return status;
 
   if(!premature && /* this check is pointless when DONE is called before the
                       entire operation is complete */
@@ -1517,10 +1553,11 @@ static CURLcode expect100(struct SessionHandle *data,
   const char *ptr;
   data->state.expect100header = FALSE; /* default to false unless it is set
                                           to TRUE below */
-  if(use_http_1_1plus(data, conn)) {
-    /* if not doing HTTP 1.0 or disabled explicitly, we add a Expect:
-       100-continue to the headers which actually speeds up post operations
-       (as there is one packet coming back from the web server) */
+  if(use_http_1_1plus(data, conn) &&
+     (conn->httpversion != 20)) {
+    /* if not doing HTTP 1.0 or version 2, or disabled explicitly, we add an
+       Expect: 100-continue to the headers which actually speeds up post
+       operations (as there is one packet coming back from the web server) */
     ptr = Curl_checkheaders(conn, "Expect:");
     if(ptr) {
       data->state.expect100header =
@@ -1529,7 +1566,7 @@ static CURLcode expect100(struct SessionHandle *data,
     else {
       result = Curl_add_bufferf(req_buffer,
                          "Expect: 100-continue\r\n");
-      if(result == CURLE_OK)
+      if(!result)
         data->state.expect100header = TRUE;
     }
   }
@@ -1659,10 +1696,8 @@ CURLcode Curl_add_timecondition(struct SessionHandle *data,
 {
   const struct tm *tm;
   char *buf = data->state.buffer;
-  CURLcode result = CURLE_OK;
   struct tm keeptime;
-
-  result = Curl_gmtime(data->set.timevalue, &keeptime);
+  CURLcode result = Curl_gmtime(data->set.timevalue, &keeptime);
   if(result) {
     failf(data, "Invalid TIMEVALUE");
     return result;
@@ -1713,8 +1748,8 @@ CURLcode Curl_add_timecondition(struct SessionHandle *data,
  */
 CURLcode Curl_http(struct connectdata *conn, bool *done)
 {
-  struct SessionHandle *data=conn->data;
-  CURLcode result=CURLE_OK;
+  struct SessionHandle *data = conn->data;
+  CURLcode result = CURLE_OK;
   struct HTTP *http;
   const char *ppath = data->state.path;
   bool paste_ftp_userpwd = FALSE;
@@ -1724,7 +1759,9 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
   const char *ptr;
   const char *request;
   Curl_HttpReq httpreq = data->set.httpreq;
+#if !defined(CURL_DISABLE_COOKIES)
   char *addcookies = NULL;
+#endif
   curl_off_t included_body = 0;
   const char *httpstring;
   Curl_send_buffer *req_buffer;
@@ -1738,8 +1775,9 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
 
   if(conn->httpversion < 20) { /* unless the connection is re-used and already
                                   http2 */
-    switch (conn->negnpn) {
-    case NPN_HTTP2:
+    switch(conn->negnpn) {
+    case CURL_HTTP_VERSION_2_0:
+      conn->httpversion = 20; /* we know we're on HTTP/2 now */
       result = Curl_http2_init(conn);
       if(result)
         return result;
@@ -1748,11 +1786,11 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
       if(result)
         return result;
 
-      result = Curl_http2_switched(conn);
+      result = Curl_http2_switched(conn, NULL, 0);
       if(result)
         return result;
       break;
-    case NPN_HTTP1_1:
+    case CURL_HTTP_VERSION_1_1:
       /* continue with HTTP/1.1 when explicitly requested */
       break;
     default:
@@ -1770,10 +1808,8 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
   http = data->req.protop;
 
   if(!data->state.this_is_a_follow) {
-    /* this is not a followed location, get the original host name */
-    if(data->state.first_host)
-      /* Free to avoid leaking memory on multiple requests*/
-      free(data->state.first_host);
+    /* Free to avoid leaking memory on multiple requests*/
+    free(data->state.first_host);
 
     data->state.first_host = strdup(conn->host.name);
     if(!data->state.first_host)
@@ -1817,7 +1853,7 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
      it might have been used in the proxy connect, but if we have got a header
      with the user-agent string specified, we erase the previously made string
      here. */
-  if(Curl_checkheaders(conn, "User-Agent:") && conn->allocptr.uagent) {
+  if(Curl_checkheaders(conn, "User-Agent:")) {
     free(conn->allocptr.uagent);
     conn->allocptr.uagent=NULL;
   }
@@ -1846,8 +1882,10 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
   else
     conn->allocptr.ref = NULL;
 
+#if !defined(CURL_DISABLE_COOKIES)
   if(data->set.str[STRING_COOKIE] && !Curl_checkheaders(conn, "Cookie:"))
     addcookies = data->set.str[STRING_COOKIE];
+#endif
 
   if(!Curl_checkheaders(conn, "Accept-Encoding:") &&
      data->set.str[STRING_ENCODING]) {
@@ -1958,7 +1996,14 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
     }
 #endif
 
-    conn->allocptr.host = NULL;
+    if(strcmp("Host:", ptr)) {
+      conn->allocptr.host = aprintf("%s\r\n", ptr);
+      if(!conn->allocptr.host)
+        return CURLE_OUT_OF_MEMORY;
+    }
+    else
+      /* when clearing the header */
+      conn->allocptr.host = NULL;
   }
   else {
     /* When building Host: headers, we must put the host name within
@@ -2153,17 +2198,15 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
     if(((httpreq == HTTPREQ_GET) || (httpreq == HTTPREQ_HEAD)) &&
        !Curl_checkheaders(conn, "Range:")) {
       /* if a line like this was already allocated, free the previous one */
-      if(conn->allocptr.rangeline)
-        free(conn->allocptr.rangeline);
+      free(conn->allocptr.rangeline);
       conn->allocptr.rangeline = aprintf("Range: bytes=%s\r\n",
                                          data->state.range);
     }
     else if((httpreq != HTTPREQ_GET) &&
             !Curl_checkheaders(conn, "Content-Range:")) {
 
       /* if a line like this was already allocated, free the previous one */
-      if(conn->allocptr.rangeline)
-        free(conn->allocptr.rangeline);
+      free(conn->allocptr.rangeline);
 
       if(data->set.set_resume_from < 0) {
         /* Upload resume was asked for, but we don't know the size of the
@@ -2227,11 +2270,11 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
     Curl_add_bufferf(req_buffer,
                      "%s" /* ftp typecode (;type=x) */
                      " HTTP/%s\r\n" /* HTTP version */
+                     "%s" /* host */
                      "%s" /* proxyuserpwd */
                      "%s" /* userpwd */
                      "%s" /* range */
                      "%s" /* user agent */
-                     "%s" /* host */
                      "%s" /* accept */
                      "%s" /* TE: */
                      "%s" /* accept-encoding */
@@ -2241,6 +2284,7 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
 
                      ftp_typecode,
                      httpstring,
+                     (conn->allocptr.host?conn->allocptr.host:""),
                      conn->allocptr.proxyuserpwd?
                      conn->allocptr.proxyuserpwd:"",
                      conn->allocptr.userpwd?conn->allocptr.userpwd:"",
@@ -2250,7 +2294,6 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
                       *data->set.str[STRING_USERAGENT] &&
                       conn->allocptr.uagent)?
                      conn->allocptr.uagent:"",
-                     (conn->allocptr.host?conn->allocptr.host:""),
                      http->p_accept?http->p_accept:"",
                      conn->allocptr.te?conn->allocptr.te:"",
                      (data->set.str[STRING_ENCODING] &&
@@ -2266,18 +2309,26 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
                      te
       );
 
+  /* clear userpwd to avoid re-using credentials from re-used connections */
+  Curl_safefree(conn->allocptr.userpwd);
+
   /*
-   * Free userpwd now --- cannot reuse this for Negotiate and possibly NTLM
-   * with basic and digest, it will be freed anyway by the next request
+   * Free proxyuserpwd for Negotiate/NTLM. Cannot reuse as it is associated
+   * with the connection and shouldn't be repeated over it either.
    */
-
-  Curl_safefree (conn->allocptr.userpwd);
-  conn->allocptr.userpwd = NULL;
+  switch (data->state.authproxy.picked) {
+  case CURLAUTH_NEGOTIATE:
+  case CURLAUTH_NTLM:
+  case CURLAUTH_NTLM_WB:
+    Curl_safefree(conn->allocptr.proxyuserpwd);
+    break;
+  }
 
   if(result)
     return result;
 
   if(!(conn->handler->flags&PROTOPT_SSL) &&
+     conn->httpversion != 20 &&
      (data->set.httpversion == CURL_HTTP_VERSION_2_0)) {
     /* append HTTP2 upgrade magic stuff to the HTTP request if it isn't done
        over SSL */
@@ -2322,17 +2373,16 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
       }
       Curl_cookie_freelist(store, FALSE); /* free the cookie list */
     }
-    if(addcookies && (CURLE_OK == result)) {
+    if(addcookies && !result) {
       if(!count)
         result = Curl_add_bufferf(req_buffer, "Cookie: ");
-      if(CURLE_OK == result) {
-        result = Curl_add_bufferf(req_buffer, "%s%s",
-                                  count?"; ":"",
+      if(!result) {
+        result = Curl_add_bufferf(req_buffer, "%s%s", count?"; ":"",
                                   addcookies);
         count++;
       }
     }
-    if(count && (CURLE_OK == result))
+    if(count && !result)
       result = Curl_add_buffer(req_buffer, "\r\n", 2);
 
     if(result)
@@ -2384,14 +2434,14 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
 
     /* Get the currently set callback function pointer and store that in the
        form struct since we might want the actual user-provided callback later
-       on. The conn->fread_func pointer itself will be changed for the
+       on. The data->set.fread_func pointer itself will be changed for the
        multipart case to the function that returns a multipart formatted
        stream. */
-    http->form.fread_func = conn->fread_func;
+    http->form.fread_func = data->set.fread_func;
 
     /* Set the read function to read from the generated form data */
-    conn->fread_func = (curl_read_callback)Curl_FormReader;
-    conn->fread_in = &http->form;
+    data->set.fread_func = (curl_read_callback)Curl_FormReader;
+    data->set.in = &http->form;
 
     http->sending = HTTPSEND_BODY;
 
@@ -2511,8 +2561,8 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
       postsize = 0;
     else {
       /* figure out the size of the postfields */
-      postsize = (data->set.postfieldsize != -1)?
-        data->set.postfieldsize:
+      postsize = (data->state.infilesize != -1)?
+        data->state.infilesize:
         (data->set.postfields? (curl_off_t)strlen(data->set.postfields):-1);
     }
 
@@ -2584,17 +2634,16 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
           if(postsize) {
             /* Append the POST data chunky-style */
             result = Curl_add_bufferf(req_buffer, "%x\r\n", (int)postsize);
-            if(CURLE_OK == result) {
+            if(!result) {
               result = Curl_add_buffer(req_buffer, data->set.postfields,
                                        (size_t)postsize);
-              if(CURLE_OK == result)
-                 result = Curl_add_buffer(req_buffer, "\r\n", 2);
+              if(!result)
+                result = Curl_add_buffer(req_buffer, "\r\n", 2);
               included_body = postsize + 2;
             }
           }
-          if(CURLE_OK == result)
-            result = Curl_add_buffer(req_buffer,
-                                     "\x30\x0d\x0a\x0d\x0a", 5);
+          if(!result)
+            result = Curl_add_buffer(req_buffer, "\x30\x0d\x0a\x0d\x0a", 5);
           /* 0  CR  LF  CR  LF */
           included_body += 5;
         }
@@ -2610,8 +2659,8 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
 
         http->sending = HTTPSEND_BODY;
 
-        conn->fread_func = (curl_read_callback)readmoredata;
-        conn->fread_in = (void *)conn;
+        data->set.fread_func = (curl_read_callback)readmoredata;
+        data->set.in = (void *)conn;
 
         /* set the upload size to the progress meter */
         Curl_pgrsSetUploadSize(data, http->postsize);
@@ -2636,7 +2685,7 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
           return result;
       }
 
-      else if(data->set.postfieldsize) {
+      else if(data->state.infilesize) {
         /* set the upload size to the progress meter */
         Curl_pgrsSetUploadSize(data, postsize?postsize:-1);
 
@@ -2997,10 +3046,12 @@ CURLcode Curl_http_readwrite_headers(struct SessionHandle *data,
             infof(data, "Received 101\n");
             k->upgr101 = UPGR101_RECEIVED;
 
-            /* switch to http2 now */
-            result = Curl_http2_switched(conn);
+            /* switch to http2 now. The bytes after response headers
+               are also processed here, otherwise they are lost. */
+            result = Curl_http2_switched(conn, k->str, *nread);
             if(result)
               return result;
+            *nread = 0;
           }
           break;
         default:
@@ -3025,6 +3076,19 @@ CURLcode Curl_http_readwrite_headers(struct SessionHandle *data,
         }
       }
 
+      /* At this point we have some idea about the fate of the connection.
+         If we are closing the connection it may result auth failure. */
+#if defined(USE_NTLM)
+      if(conn->bits.close &&
+         (((data->req.httpcode == 401) &&
+           (conn->ntlm.state == NTLMSTATE_TYPE2)) ||
+          ((data->req.httpcode == 407) &&
+           (conn->proxyntlm.state == NTLMSTATE_TYPE2)))) {
+        infof(data, "Connection closure while negotiating auth (HTTP 1.0?)\n");
+        data->state.authproblem = TRUE;
+      }
+#endif
+
       /*
        * When all the headers have been parsed, see if we should give
        * up and return an error.
@@ -3203,13 +3267,26 @@ CURLcode Curl_http_readwrite_headers(struct SessionHandle *data,
 #endif /* CURL_DOES_CONVERSIONS */
 
       if(conn->handler->protocol & PROTO_FAMILY_HTTP) {
+        /*
+         * https://tools.ietf.org/html/rfc7230#section-3.1.2
+         *
+         * The reponse code is always a three-digit number in HTTP as the spec
+         * says. We try to allow any number here, but we cannot make
+         * guarantees on future behaviors since it isn't within the protocol.
+         */
         nc = sscanf(HEADER1,
-                    " HTTP/%d.%d %3d",
+                    " HTTP/%d.%d %d",
                     &httpversion_major,
                     &conn->httpversion,
                     &k->httpcode);
         if(nc==3) {
           conn->httpversion += 10 * httpversion_major;
+
+          if(k->upgr101 == UPGR101_RECEIVED) {
+            /* supposedly upgraded to http2 now */
+            if(conn->httpversion != 20)
+              infof(data, "Lying server, not serving HTTP/2\n");
+          }
         }
         else {
           /* this is the real world, not a Nirvana
@@ -3287,20 +3364,25 @@ CURLcode Curl_http_readwrite_headers(struct SessionHandle *data,
           infof(data, "HTTP 1.0, assume close after body\n");
           connclose(conn, "HTTP/1.0 close after body");
         }
+        else if(conn->httpversion == 20 ||
+                (k->upgr101 == UPGR101_REQUESTED && k->httpcode == 101)) {
+          DEBUGF(infof(data, "HTTP/2 found, allow multiplexing\n"));
+
+          /* HTTP/2 cannot blacklist multiplexing since it is a core
+             functionality of the protocol */
+          conn->bundle->multiuse = BUNDLE_MULTIPLEX;
+        }
         else if(conn->httpversion >= 11 &&
                 !conn->bits.close) {
-          struct connectbundle *cb_ptr;
-
           /* If HTTP version is >= 1.1 and connection is persistent
              server supports pipelining. */
           DEBUGF(infof(data,
                        "HTTP 1.1 or later with persistent connection, "
                        "pipelining supported\n"));
           /* Activate pipelining if needed */
-          cb_ptr = conn->bundle;
-          if(cb_ptr) {
+          if(conn->bundle) {
             if(!Curl_pipeline_site_blacklisted(data, conn))
-              cb_ptr->server_supports_pipelining = TRUE;
+              conn->bundle->multiuse = BUNDLE_PIPELINING;
           }
         }
 
@@ -3379,14 +3461,17 @@ CURLcode Curl_http_readwrite_headers(struct SessionHandle *data,
       }
     }
     else if(checkprefix("Server:", k->p)) {
-      char *server_name = Curl_copy_header_value(k->p);
-
-      /* Turn off pipelining if the server version is blacklisted */
-      if(conn->bundle && conn->bundle->server_supports_pipelining) {
-        if(Curl_pipeline_server_blacklisted(data, server_name))
-          conn->bundle->server_supports_pipelining = FALSE;
+      if(conn->httpversion < 20) {
+        /* only do this for non-h2 servers */
+        char *server_name = Curl_copy_header_value(k->p);
+
+        /* Turn off pipelining if the server version is blacklisted  */
+        if(conn->bundle && (conn->bundle->multiuse == BUNDLE_PIPELINING)) {
+          if(Curl_pipeline_server_blacklisted(data, server_name))
+            conn->bundle->multiuse = BUNDLE_NO_MULTIUSE;
+        }
+        free(server_name);
       }
-      Curl_safefree(server_name);
     }
     else if((conn->httpversion == 10) &&
             conn->bits.httpproxy &&
@@ -3483,14 +3568,6 @@ CURLcode Curl_http_readwrite_headers(struct SessionHandle *data,
           k->auto_decoding = GZIP;
           start += 6;
         }
-        else if(checkprefix("compress", start)) {
-          k->auto_decoding = COMPRESS;
-          start += 8;
-        }
-        else if(checkprefix("x-compress", start)) {
-          k->auto_decoding = COMPRESS;
-          start += 10;
-        }
         else
           /* unknown! */
           break;
@@ -3523,9 +3600,6 @@ CURLcode Curl_http_readwrite_headers(struct SessionHandle *data,
       else if(checkprefix("gzip", start)
               || checkprefix("x-gzip", start))
         k->auto_decoding = GZIP;
-      else if(checkprefix("compress", start)
-              || checkprefix("x-compress", start))
-        k->auto_decoding = COMPRESS;
     }
     else if(checkprefix("Content-Range:", k->p)) {
       /* Content-Range: bytes [num]-
@@ -3591,7 +3665,7 @@ CURLcode Curl_http_readwrite_headers(struct SessionHandle *data,
 
       result = Curl_http_input_auth(conn, proxy, auth);
 
-      Curl_safefree(auth);
+      free(auth);
 
       if(result)
         return result;