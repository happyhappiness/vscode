@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2017, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -297,7 +297,8 @@ static CURLcode http_output_basic(struct connectdata *conn, bool proxy)
     pwd = conn->passwd;
   }
 
-  snprintf(data->state.buffer, sizeof(data->state.buffer), "%s:%s", user, pwd);
+  snprintf(data->state.buffer, CURL_BUFSIZE(data->set.buffer_size),
+           "%s:%s", user, pwd);
 
   result = Curl_base64_encode(data,
                               data->state.buffer, strlen(data->state.buffer),
@@ -644,10 +645,10 @@ output_auth_headers(struct connectdata *conn,
           proxy ? "Proxy" : "Server", auth,
           proxy ? (conn->http_proxy.user ? conn->http_proxy.user : "") :
                   (conn->user ? conn->user : ""));
-    authstatus->multi = (!authstatus->done) ? TRUE : FALSE;
+    authstatus->multipass = (!authstatus->done) ? TRUE : FALSE;
   }
   else
-    authstatus->multi = FALSE;
+    authstatus->multipass = FALSE;
 
   return CURLE_OK;
 }
@@ -1196,8 +1197,7 @@ CURLcode Curl_add_buffer_send(Curl_send_buffer *in,
            This needs FIXing.
         */
         return CURLE_SEND_ERROR;
-      else
-        Curl_pipeline_leave_write(conn);
+      Curl_pipeline_leave_write(conn);
     }
   }
   Curl_add_buffer_free(in);
@@ -1358,14 +1358,18 @@ CURLcode Curl_http_connect(struct connectdata *conn, bool *done)
   if(result)
     return result;
 
+  if(conn->bits.proxy_connect_closed)
+    /* this is not an error, just part of the connection negotiation */
+    return CURLE_OK;
+
   if(CONNECT_FIRSTSOCKET_PROXY_SSL())
     return CURLE_OK; /* wait for HTTPS proxy SSL initialization to complete */
 
   if(conn->tunnel_state[FIRSTSOCKET] == TUNNEL_CONNECT)
     /* nothing else to do except wait right now - we're not done here. */
     return CURLE_OK;
 
-  if(conn->given->flags & PROTOPT_SSL) {
+  if(conn->given->protocol & CURLPROTO_HTTPS) {
     /* perform SSL initialization */
     result = https_connecting(conn, done);
     if(result)
@@ -1425,7 +1429,10 @@ CURLcode Curl_http_done(struct connectdata *conn,
   struct Curl_easy *data = conn->data;
   struct HTTP *http = data->req.protop;
 
-  infof(data, "Curl_http_done: called premature == %d\n", premature);
+  /* Clear multipass flag. If authentication isn't done yet, then it will get
+   * a chance to be set back to true when we output the next auth header */
+  data->state.authhost.multipass = FALSE;
+  data->state.authproxy.multipass = FALSE;
 
   Curl_unencode_cleanup(conn);
 
@@ -1511,6 +1518,20 @@ static bool use_http_1_1plus(const struct Curl_easy *data,
           (data->set.httpversion >= CURL_HTTP_VERSION_1_1));
 }
 
+static const char *get_http_string(const struct Curl_easy *data,
+                                   const struct connectdata *conn)
+{
+#ifdef USE_NGHTTP2
+  if(conn->proto.httpc.h2)
+    return "2";
+#endif
+
+  if(use_http_1_1plus(data, conn))
+    return "1.1";
+
+  return "1.0";
+}
+
 /* check and possibly add an Expect: header */
 static CURLcode expect100(struct Curl_easy *data,
                           struct connectdata *conn,
@@ -1849,7 +1870,7 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
   if(result)
     return result;
 
-  if((data->state.authhost.multi || data->state.authproxy.multi) &&
+  if((data->state.authhost.multipass || data->state.authproxy.multipass) &&
      (httpreq != HTTPREQ_GET) &&
      (httpreq != HTTPREQ_HEAD)) {
     /* Auth is required and we are not authenticated yet. Make a PUT or POST
@@ -2134,32 +2155,31 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
       }
 
       if(seekerr != CURL_SEEKFUNC_OK) {
+        curl_off_t passed=0;
+
         if(seekerr != CURL_SEEKFUNC_CANTSEEK) {
           failf(data, "Could not seek stream");
           return CURLE_READ_ERROR;
         }
         /* when seekerr == CURL_SEEKFUNC_CANTSEEK (can't seek to offset) */
-        else {
-          curl_off_t passed=0;
-          do {
-            size_t readthisamountnow =
-              (data->state.resume_from - passed > CURL_OFF_T_C(BUFSIZE)) ?
-              BUFSIZE : curlx_sotouz(data->state.resume_from - passed);
-
-            size_t actuallyread =
-              data->state.fread_func(data->state.buffer, 1, readthisamountnow,
-                                     data->state.in);
-
-            passed += actuallyread;
-            if((actuallyread == 0) || (actuallyread > readthisamountnow)) {
-              /* this checks for greater-than only to make sure that the
-                 CURL_READFUNC_ABORT return code still aborts */
-              failf(data, "Could only read %" CURL_FORMAT_CURL_OFF_T
-                    " bytes from the input", passed);
-              return CURLE_READ_ERROR;
-            }
-          } while(passed < data->state.resume_from);
-        }
+        do {
+          size_t readthisamountnow =
+            (data->state.resume_from - passed > CURL_OFF_T_C(BUFSIZE)) ?
+            BUFSIZE : curlx_sotouz(data->state.resume_from - passed);
+
+          size_t actuallyread =
+            data->state.fread_func(data->state.buffer, 1, readthisamountnow,
+                                   data->state.in);
+
+          passed += actuallyread;
+          if((actuallyread == 0) || (actuallyread > readthisamountnow)) {
+            /* this checks for greater-than only to make sure that the
+               CURL_READFUNC_ABORT return code still aborts */
+            failf(data, "Could only read %" CURL_FORMAT_CURL_OFF_T
+                  " bytes from the input", passed);
+            return CURLE_READ_ERROR;
+          }
+        } while(passed < data->state.resume_from);
       }
 
       /* now, decrease the size of the read */
@@ -2225,9 +2245,7 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
     }
   }
 
-  /* Use 1.1 unless the user specifically asked for 1.0 or the server only
-     supports 1.0 */
-  httpstring= use_http_1_1plus(data, conn)?"1.1":"1.0";
+  httpstring = get_http_string(data, conn);
 
   /* initialize a dynamic send-buffer */
   req_buffer = Curl_add_buffer_init();
@@ -2294,20 +2312,10 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
                      te
       );
 
-  /* clear userpwd to avoid re-using credentials from re-used connections */
+  /* clear userpwd and proxyuserpwd to avoid re-using old credentials
+   * from re-used connections */
   Curl_safefree(conn->allocptr.userpwd);
-
-  /*
-   * Free proxyuserpwd for Negotiate/NTLM. Cannot reuse as it is associated
-   * with the connection and shouldn't be repeated over it either.
-   */
-  switch(data->state.authproxy.picked) {
-  case CURLAUTH_NEGOTIATE:
-  case CURLAUTH_NTLM:
-  case CURLAUTH_NTLM_WB:
-    Curl_safefree(conn->allocptr.proxyuserpwd);
-    break;
-  }
+  Curl_safefree(conn->allocptr.proxyuserpwd);
 
   if(result)
     return result;
@@ -2501,7 +2509,7 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
       postsize = data->state.infilesize;
 
     if((postsize != -1) && !data->req.upload_chunky &&
-       !Curl_checkheaders(conn, "Content-Length:")) {
+       (conn->bits.authneg || !Curl_checkheaders(conn, "Content-Length:"))) {
       /* only add Content-Length if not uploading chunked */
       result = Curl_add_bufferf(req_buffer,
                                 "Content-Length: %" CURL_FORMAT_CURL_OFF_T
@@ -2553,7 +2561,7 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
        we don't upload data chunked, as RFC2616 forbids us to set both
        kinds of headers (Transfer-Encoding: chunked and Content-Length) */
     if((postsize != -1) && !data->req.upload_chunky &&
-       !Curl_checkheaders(conn, "Content-Length:")) {
+       (conn->bits.authneg || !Curl_checkheaders(conn, "Content-Length:"))) {
       /* we allow replacing this header if not during auth negotiation,
          although it isn't very wise to actually set your own */
       result = Curl_add_bufferf(req_buffer,
@@ -2807,8 +2815,7 @@ checkrtspprefix(struct Curl_easy *data,
 #endif /* CURL_DOES_CONVERSIONS */
   if(checkprefix("RTSP/", s))
     return TRUE;
-  else
-    return FALSE;
+  return FALSE;
 }
 #endif /* CURL_DISABLE_RTSP */
 
@@ -3229,9 +3236,17 @@ CURLcode Curl_http_readwrite_headers(struct Curl_easy *data,
           k->maxdownload = k->size;
         }
 
-        /* If max download size is *zero* (nothing) we already
-           have nothing and can safely return ok now! */
-        if(0 == k->maxdownload)
+        /* If max download size is *zero* (nothing) we already have
+           nothing and can safely return ok now!  But for HTTP/2, we'd
+           like to call http2_handle_stream_close to properly close a
+           stream.  In order to do this, we keep reading until we
+           close the stream. */
+        if(0 == k->maxdownload
+#if defined(USE_NGHTTP2)
+           && !((conn->handler->protocol & PROTO_FAMILY_HTTP) &&
+                conn->httpversion == 20)
+#endif
+           )
           *stop_reading = TRUE;
 
         if(*stop_reading) {
@@ -3288,7 +3303,7 @@ CURLcode Curl_http_readwrite_headers(struct Curl_easy *data,
         /*
          * https://tools.ietf.org/html/rfc7230#section-3.1.2
          *
-         * The reponse code is always a three-digit number in HTTP as the spec
+         * The response code is always a three-digit number in HTTP as the spec
          * says. We try to allow any number here, but we cannot make
          * guarantees on future behaviors since it isn't within the protocol.
          */