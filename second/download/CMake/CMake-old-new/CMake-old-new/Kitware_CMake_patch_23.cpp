@@ -285,6 +285,7 @@ static CURLcode http_output_basic(struct connectdata *conn, bool proxy)
   const char *user;
   const char *pwd;
   CURLcode result;
+  char *out;
 
   if(proxy) {
     userp = &conn->allocptr.proxyuserpwd;
@@ -297,27 +298,32 @@ static CURLcode http_output_basic(struct connectdata *conn, bool proxy)
     pwd = conn->passwd;
   }
 
-  snprintf(data->state.buffer, CURL_BUFSIZE(data->set.buffer_size),
-           "%s:%s", user, pwd);
+  out = aprintf("%s:%s", user, pwd);
+  if(!out)
+    return CURLE_OUT_OF_MEMORY;
 
-  result = Curl_base64_encode(data,
-                              data->state.buffer, strlen(data->state.buffer),
-                              &authorization, &size);
+  result = Curl_base64_encode(data, out, strlen(out), &authorization, &size);
   if(result)
-    return result;
+    goto fail;
 
-  if(!authorization)
-    return CURLE_REMOTE_ACCESS_DENIED;
+  if(!authorization) {
+    result = CURLE_REMOTE_ACCESS_DENIED;
+    goto fail;
+  }
 
   free(*userp);
   *userp = aprintf("%sAuthorization: Basic %s\r\n",
                    proxy ? "Proxy-" : "",
                    authorization);
   free(authorization);
-  if(!*userp)
-    return CURLE_OUT_OF_MEMORY;
+  if(!*userp) {
+    result = CURLE_OUT_OF_MEMORY;
+    goto fail;
+  }
 
-  return CURLE_OK;
+  fail:
+  free(out);
+  return result;
 }
 
 /* pickoneauth() selects the most favourable authentication method from the
@@ -413,8 +419,6 @@ static CURLcode http_perhapsrewind(struct connectdata *conn)
     case HTTPREQ_POST:
       if(data->state.infilesize != -1)
         expectsend = data->state.infilesize;
-      else if(data->set.postfields)
-        expectsend = (curl_off_t)strlen(data->set.postfields);
       break;
     case HTTPREQ_PUT:
       if(data->state.infilesize != -1)
@@ -1111,7 +1115,7 @@ CURLcode Curl_add_buffer_send(Curl_send_buffer *in,
        buffer is using this size.
     */
 
-    sendsize = (size > CURL_MAX_WRITE_SIZE) ? CURL_MAX_WRITE_SIZE : size;
+    sendsize = CURLMIN(size, CURL_MAX_WRITE_SIZE);
 
     /* OpenSSL is very picky and we must send the SAME buffer pointer to the
        library when we attempt to re-send this buffer. Sending the same data
@@ -1689,9 +1693,10 @@ CURLcode Curl_add_timecondition(struct Curl_easy *data,
                                 Curl_send_buffer *req_buffer)
 {
   const struct tm *tm;
-  char *buf = data->state.buffer;
   struct tm keeptime;
   CURLcode result;
+  char datestr[80];
+  const char *condp;
 
   if(data->set.timecondition == CURL_TIMECOND_NONE)
     /* no condition was asked for */
@@ -1704,6 +1709,21 @@ CURLcode Curl_add_timecondition(struct Curl_easy *data,
   }
   tm = &keeptime;
 
+  switch(data->set.timecondition) {
+  default:
+    return CURLE_BAD_FUNCTION_ARGUMENT;
+
+  case CURL_TIMECOND_IFMODSINCE:
+    condp = "If-Modified-Since";
+    break;
+  case CURL_TIMECOND_IFUNMODSINCE:
+    condp = "If-Unmodified-Since";
+    break;
+  case CURL_TIMECOND_LASTMOD:
+    condp = "Last-Modified";
+    break;
+  }
+
   /* The If-Modified-Since header family should have their times set in
    * GMT as RFC2616 defines: "All HTTP date/time stamps MUST be
    * represented in Greenwich Mean Time (GMT), without exception. For the
@@ -1712,8 +1732,9 @@ CURLcode Curl_add_timecondition(struct Curl_easy *data,
    */
 
   /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
-  snprintf(buf, BUFSIZE-1,
-           "%s, %02d %s %4d %02d:%02d:%02d GMT",
+  snprintf(datestr, sizeof(datestr),
+           "%s: %s, %02d %s %4d %02d:%02d:%02d GMT\r\n",
+           condp,
            Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
            tm->tm_mday,
            Curl_month[tm->tm_mon],
@@ -1722,22 +1743,7 @@ CURLcode Curl_add_timecondition(struct Curl_easy *data,
            tm->tm_min,
            tm->tm_sec);
 
-  switch(data->set.timecondition) {
-  default:
-    break;
-  case CURL_TIMECOND_IFMODSINCE:
-    result = Curl_add_bufferf(req_buffer,
-                              "If-Modified-Since: %s\r\n", buf);
-    break;
-  case CURL_TIMECOND_IFUNMODSINCE:
-    result = Curl_add_bufferf(req_buffer,
-                              "If-Unmodified-Since: %s\r\n", buf);
-    break;
-  case CURL_TIMECOND_LASTMOD:
-    result = Curl_add_bufferf(req_buffer,
-                              "Last-Modified: %s\r\n", buf);
-    break;
-  }
+  result = Curl_add_buffer(req_buffer, datestr, strlen(datestr));
 
   return result;
 }
@@ -2164,8 +2170,9 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
         /* when seekerr == CURL_SEEKFUNC_CANTSEEK (can't seek to offset) */
         do {
           size_t readthisamountnow =
-            (data->state.resume_from - passed > CURL_OFF_T_C(BUFSIZE)) ?
-            BUFSIZE : curlx_sotouz(data->state.resume_from - passed);
+            (data->state.resume_from - passed > data->set.buffer_size) ?
+            (size_t)data->set.buffer_size :
+            curlx_sotouz(data->state.resume_from - passed);
 
           size_t actuallyread =
             data->state.fread_func(data->state.buffer, 1, readthisamountnow,
@@ -2550,12 +2557,9 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
 
     if(conn->bits.authneg)
       postsize = 0;
-    else {
-      /* figure out the size of the postfields */
-      postsize = (data->state.infilesize != -1)?
-        data->state.infilesize:
-        (data->set.postfields? (curl_off_t)strlen(data->set.postfields):-1);
-    }
+    else
+      /* the size of the post body */
+      postsize = data->state.infilesize;
 
     /* We only set Content-Length and allow a custom Content-Length if
        we don't upload data chunked, as RFC2616 forbids us to set both
@@ -2737,6 +2741,7 @@ CURLcode Curl_http(struct connectdata *conn, bool *done)
       data->req.upload_done = TRUE;
       data->req.keepon &= ~KEEP_SEND; /* we're done writing */
       data->req.exp100 = EXP100_SEND_DATA; /* already sent */
+      Curl_expire_done(data, EXPIRE_100_TIMEOUT);
     }
   }
 
@@ -3033,6 +3038,7 @@ CURLcode Curl_http_readwrite_headers(struct Curl_easy *data,
           if(k->exp100 > EXP100_SEND_DATA) {
             k->exp100 = EXP100_SEND_DATA;
             k->keepon |= KEEP_SEND;
+            Curl_expire_done(data, EXPIRE_100_TIMEOUT);
           }
           break;
         case 101:
@@ -3159,6 +3165,7 @@ CURLcode Curl_http_readwrite_headers(struct Curl_easy *data,
              * request body has been sent we stop sending and mark the
              * connection for closure after we've read the entire response.
              */
+            Curl_expire_done(data, EXPIRE_100_TIMEOUT);
             if(!k->upload_done) {
               if(data->set.http_keep_sending_on_error) {
                 infof(data, "HTTP error before end of send, keep sending\n");