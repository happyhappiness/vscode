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
@@ -23,7 +23,6 @@
 #include "curl_setup.h"
 
 #ifdef USE_NGHTTP2
-#include "curl_printf.h"
 #include <nghttp2/nghttp2.h>
 #include "urldata.h"
 #include "http2.h"
@@ -34,17 +33,50 @@
 #include "multiif.h"
 #include "conncache.h"
 #include "url.h"
+#include "connect.h"
+#include "strtoofft.h"
 
-/* The last #include files should be: */
+/* The last 3 #include files should be in this order */
+#include "curl_printf.h"
 #include "curl_memory.h"
 #include "memdebug.h"
 
 #define MIN(x,y) ((x)<(y)?(x):(y))
 
-#if (NGHTTP2_VERSION_NUM < 0x000600)
+#if (NGHTTP2_VERSION_NUM < 0x010000)
 #error too old nghttp2 version, upgrade!
 #endif
 
+#if (NGHTTP2_VERSION_NUM > 0x010800)
+#define NGHTTP2_HAS_HTTP2_STRERROR 1
+#endif
+
+#if (NGHTTP2_VERSION_NUM >= 0x010900)
+/* nghttp2_session_callbacks_set_error_callback is present in nghttp2 1.9.0 or
+   later */
+#define NGHTTP2_HAS_ERROR_CALLBACK 1
+#else
+#define nghttp2_session_callbacks_set_error_callback(x,y)
+#endif
+
+/*
+ * Curl_http2_init_state() is called when the easy handle is created and
+ * allows for HTTP/2 specific init of state.
+ */
+void Curl_http2_init_state(struct UrlState *state)
+{
+  state->stream_weight = NGHTTP2_DEFAULT_WEIGHT;
+}
+
+/*
+ * Curl_http2_init_userset() is called when the easy handle is created and
+ * allows for HTTP/2 specific user-set fields.
+ */
+void Curl_http2_init_userset(struct UserDefined *set)
+{
+  set->stream_weight = NGHTTP2_DEFAULT_WEIGHT;
+}
+
 static int http2_perform_getsock(const struct connectdata *conn,
                                  curl_socket_t *sock, /* points to
                                                          numsocks
@@ -92,6 +124,8 @@ static CURLcode http2_disconnect(struct connectdata *conn,
   if(http) {
     Curl_add_buffer_free(http->header_recvbuf);
     http->header_recvbuf = NULL; /* clear the pointer */
+    Curl_add_buffer_free(http->trailer_recvbuf);
+    http->trailer_recvbuf = NULL; /* clear the pointer */
     for(; http->push_headers_used > 0; --http->push_headers_used) {
       free(http->push_headers[http->push_headers_used - 1]);
     }
@@ -105,7 +139,7 @@ static CURLcode http2_disconnect(struct connectdata *conn,
 }
 
 /* called from Curl_http_setup_conn */
-void Curl_http2_setup_req(struct SessionHandle *data)
+void Curl_http2_setup_req(struct Curl_easy *data)
 {
   struct HTTP *http = data->req.protop;
 
@@ -134,7 +168,7 @@ void Curl_http2_setup_conn(struct connectdata *conn)
  * HTTP to HTTP2.
  */
 const struct Curl_handler Curl_handler_http2 = {
-  "HTTP2",                              /* scheme */
+  "HTTP",                               /* scheme */
   ZERO_NULL,                            /* setup_connection */
   Curl_http,                            /* do_it */
   Curl_http_done,                       /* done */
@@ -154,7 +188,7 @@ const struct Curl_handler Curl_handler_http2 = {
 };
 
 const struct Curl_handler Curl_handler_http2_ssl = {
-  "HTTP2",                              /* scheme */
+  "HTTPS",                              /* scheme */
   ZERO_NULL,                            /* setup_connection */
   Curl_http,                            /* do_it */
   Curl_http_done,                       /* done */
@@ -183,6 +217,34 @@ int Curl_http2_ver(char *p, size_t len)
   return snprintf(p, len, " nghttp2/%s", h2->version_str);
 }
 
+/* HTTP/2 error code to name based on the Error Code Registry.
+https://tools.ietf.org/html/rfc7540#page-77
+nghttp2_error_code enums are identical.
+*/
+const char *Curl_http2_strerror(uint32_t err) {
+#ifndef NGHTTP2_HAS_HTTP2_STRERROR
+  const char *str[] = {
+    "NO_ERROR",             /* 0x0 */
+    "PROTOCOL_ERROR",       /* 0x1 */
+    "INTERNAL_ERROR",       /* 0x2 */
+    "FLOW_CONTROL_ERROR",   /* 0x3 */
+    "SETTINGS_TIMEOUT",     /* 0x4 */
+    "STREAM_CLOSED",        /* 0x5 */
+    "FRAME_SIZE_ERROR",     /* 0x6 */
+    "REFUSED_STREAM",       /* 0x7 */
+    "CANCEL",               /* 0x8 */
+    "COMPRESSION_ERROR",    /* 0x9 */
+    "CONNECT_ERROR",        /* 0xA */
+    "ENHANCE_YOUR_CALM",    /* 0xB */
+    "INADEQUATE_SECURITY",  /* 0xC */
+    "HTTP_1_1_REQUIRED"     /* 0xD */
+  };
+  return (err < sizeof str / sizeof str[0]) ? str[err] : "unknown";
+#else
+  return nghttp2_http2_strerror(err);
+#endif
+}
+
 /*
  * The implementation of nghttp2_send_callback type. Here we write |data| with
  * size |length| to the network and return the number of bytes actually
@@ -222,7 +284,7 @@ static ssize_t send_callback(nghttp2_session *h2,
 /* We pass a pointer to this struct in the push callback, but the contents of
    the struct are hidden from the user. */
 struct curl_pushheaders {
-  struct SessionHandle *data;
+  struct Curl_easy *data;
   const nghttp2_push_promise *frame;
 };
 
@@ -263,7 +325,7 @@ char *curl_pushheader_byname(struct curl_pushheaders *h, const char *header)
     size_t i;
     for(i=0; i<stream->push_headers_used; i++) {
       if(!strncmp(header, stream->push_headers[i], len)) {
-        /* sub-match, make sure that it us followed by a colon */
+        /* sub-match, make sure that it is followed by a colon */
         if(stream->push_headers[i][len] != ':')
           continue;
         return &stream->push_headers[i][len+1];
@@ -273,9 +335,9 @@ char *curl_pushheader_byname(struct curl_pushheaders *h, const char *header)
   return NULL;
 }
 
-static CURL *duphandle(struct SessionHandle *data)
+static struct Curl_easy *duphandle(struct Curl_easy *data)
 {
-  struct SessionHandle *second = curl_easy_duphandle(data);
+  struct Curl_easy *second = curl_easy_duphandle(data);
   if(second) {
     /* setup the request struct */
     struct HTTP *http = calloc(1, sizeof(struct HTTP));
@@ -291,15 +353,17 @@ static CURL *duphandle(struct SessionHandle *data)
         (void)Curl_close(second);
         second = NULL;
       }
-      else
+      else {
         Curl_http2_setup_req(second);
+        second->state.stream_weight = data->state.stream_weight;
+      }
     }
   }
   return second;
 }
 
 
-static int push_promise(struct SessionHandle *data,
+static int push_promise(struct Curl_easy *data,
                         struct connectdata *conn,
                         const nghttp2_push_promise *frame)
 {
@@ -308,12 +372,13 @@ static int push_promise(struct SessionHandle *data,
                frame->promised_stream_id));
   if(data->multi->push_cb) {
     struct HTTP *stream;
+    struct HTTP *newstream;
     struct curl_pushheaders heads;
     CURLMcode rc;
     struct http_conn *httpc;
     size_t i;
     /* clone the parent */
-    CURL *newhandle = duphandle(data);
+    struct Curl_easy *newhandle = duphandle(data);
     if(!newhandle) {
       infof(data, "failed to duplicate handle\n");
       rv = 1; /* FAIL HARD */
@@ -348,6 +413,11 @@ static int push_promise(struct SessionHandle *data,
       goto fail;
     }
 
+    newstream = newhandle->req.protop;
+    newstream->stream_id = frame->promised_stream_id;
+    newhandle->req.maxdownload = -1;
+    newhandle->req.size = -1;
+
     /* approved, add to the multi handle and immediately switch to PERFORM
        state with the given connection !*/
     rc = Curl_multi_add_perform(data->multi, newhandle, conn);
@@ -373,29 +443,46 @@ static int push_promise(struct SessionHandle *data,
 static int on_frame_recv(nghttp2_session *session, const nghttp2_frame *frame,
                          void *userp)
 {
-  struct connectdata *conn = NULL;
-  struct http_conn *httpc = NULL;
-  struct SessionHandle *data_s = NULL;
+  struct connectdata *conn = (struct connectdata *)userp;
+  struct http_conn *httpc = &conn->proto.httpc;
+  struct Curl_easy *data_s = NULL;
   struct HTTP *stream = NULL;
   static int lastStream = -1;
   int rv;
   size_t left, ncopy;
   int32_t stream_id = frame->hd.stream_id;
 
-  (void)userp;
-
   if(!stream_id) {
     /* stream ID zero is for connection-oriented stuff */
+    if(frame->hd.type == NGHTTP2_SETTINGS) {
+      uint32_t max_conn = httpc->settings.max_concurrent_streams;
+      DEBUGF(infof(conn->data, "Got SETTINGS\n"));
+      httpc->settings.max_concurrent_streams =
+        nghttp2_session_get_remote_settings(
+          session, NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS);
+      httpc->settings.enable_push =
+        nghttp2_session_get_remote_settings(
+          session, NGHTTP2_SETTINGS_ENABLE_PUSH);
+      DEBUGF(infof(conn->data, "MAX_CONCURRENT_STREAMS == %d\n",
+                   httpc->settings.max_concurrent_streams));
+      DEBUGF(infof(conn->data, "ENABLE_PUSH == %s\n",
+                   httpc->settings.enable_push?"TRUE":"false"));
+      if(max_conn != httpc->settings.max_concurrent_streams) {
+        /* only signal change if the value actually changed */
+        infof(conn->data,
+              "Connection state changed (MAX_CONCURRENT_STREAMS updated)!\n");
+        Curl_multi_connchanged(conn->data->multi);
+      }
+    }
     return 0;
   }
-  data_s = nghttp2_session_get_stream_user_data(session,
-                                                frame->hd.stream_id);
-  if(lastStream != frame->hd.stream_id) {
-    lastStream = frame->hd.stream_id;
+  data_s = nghttp2_session_get_stream_user_data(session, stream_id);
+  if(lastStream != stream_id) {
+    lastStream = stream_id;
   }
   if(!data_s) {
     DEBUGF(infof(conn->data,
-                 "No SessionHandle associated with stream: %x\n",
+                 "No Curl_easy associated with stream: %x\n",
                  stream_id));
     return 0;
   }
@@ -407,10 +494,6 @@ static int on_frame_recv(nghttp2_session *session, const nghttp2_frame *frame,
   DEBUGF(infof(data_s, "on_frame_recv() header %x stream %x\n",
                frame->hd.type, stream_id));
 
-  conn = data_s->easy_conn;
-  assert(conn);
-  assert(conn->data == data_s);
-  httpc = &conn->proto.httpc;
   switch(frame->hd.type) {
   case NGHTTP2_DATA:
     /* If body started on this stream, then receiving DATA is illegal. */
@@ -424,13 +507,9 @@ static int on_frame_recv(nghttp2_session *session, const nghttp2_frame *frame,
     }
     break;
   case NGHTTP2_HEADERS:
-    if(frame->headers.cat == NGHTTP2_HCAT_REQUEST)
-      break;
-
     if(stream->bodystarted) {
       /* Only valid HEADERS after body started is trailer HEADERS.  We
-         ignores trailer HEADERS for now.  nghttp2 guarantees that it
-         has END_STREAM flag set. */
+         buffer them in on_header callback. */
       break;
     }
 
@@ -461,7 +540,15 @@ static int on_frame_recv(nghttp2_session *session, const nghttp2_frame *frame,
     stream->memlen += ncopy;
 
     data_s->state.drain++;
-    Curl_expire(data_s, 1);
+    httpc->drain_total++;
+    {
+      /* get the pointer from userp again since it was re-assigned above */
+      struct connectdata *conn_s = (struct connectdata *)userp;
+
+      /* if we receive data for another handle, wake that up */
+      if(conn_s->data != data_s)
+        Curl_expire(data_s, 1);
+    }
     break;
   case NGHTTP2_PUSH_PROMISE:
     rv = push_promise(data_s, conn, &frame->push_promise);
@@ -474,28 +561,6 @@ static int on_frame_recv(nghttp2_session *session, const nghttp2_frame *frame,
       }
     }
     break;
-  case NGHTTP2_SETTINGS:
-  {
-    uint32_t max_conn = httpc->settings.max_concurrent_streams;
-    DEBUGF(infof(conn->data, "Got SETTINGS for stream %u!\n", stream_id));
-    httpc->settings.max_concurrent_streams =
-      nghttp2_session_get_remote_settings(
-        session, NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS);
-    httpc->settings.enable_push =
-      nghttp2_session_get_remote_settings(
-        session, NGHTTP2_SETTINGS_ENABLE_PUSH);
-    DEBUGF(infof(conn->data, "MAX_CONCURRENT_STREAMS == %d\n",
-                 httpc->settings.max_concurrent_streams));
-    DEBUGF(infof(conn->data, "ENABLE_PUSH == %s\n",
-                 httpc->settings.enable_push?"TRUE":"false"));
-    if(max_conn != httpc->settings.max_concurrent_streams) {
-      /* only signal change if the value actually changed */
-      infof(conn->data,
-            "Connection state changed (MAX_CONCURRENT_STREAMS updated)!\n");
-      Curl_multi_connchanged(conn->data->multi);
-    }
-  }
-  break;
   default:
     DEBUGF(infof(conn->data, "Got frame type %x for stream %u!\n",
                  frame->hd.type, stream_id));
@@ -508,7 +573,7 @@ static int on_invalid_frame_recv(nghttp2_session *session,
                                  const nghttp2_frame *frame,
                                  int lib_error_code, void *userp)
 {
-  struct SessionHandle *data_s = NULL;
+  struct Curl_easy *data_s = NULL;
   (void)userp;
 
   data_s = nghttp2_session_get_stream_user_data(session, frame->hd.stream_id);
@@ -525,12 +590,12 @@ static int on_data_chunk_recv(nghttp2_session *session, uint8_t flags,
                               const uint8_t *data, size_t len, void *userp)
 {
   struct HTTP *stream;
-  struct SessionHandle *data_s;
+  struct Curl_easy *data_s;
   size_t nread;
+  struct connectdata *conn = (struct connectdata *)userp;
   (void)session;
   (void)flags;
   (void)data;
-  (void)userp;
 
   DEBUGASSERT(stream_id); /* should never be a zero stream ID here */
 
@@ -552,8 +617,12 @@ static int on_data_chunk_recv(nghttp2_session *session, uint8_t flags,
   stream->memlen += nread;
 
   data_s->state.drain++;
-  Curl_expire(data_s, 1); /* TODO: fix so that this can be set to 0 for
-                             immediately? */
+  conn->proto.httpc.drain_total++;
+
+  /* if we receive data for another handle, wake that up */
+  if(conn->data != data_s)
+    Curl_expire(data_s, 1); /* TODO: fix so that this can be set to 0 for
+                               immediately? */
 
   DEBUGF(infof(data_s, "%zu data received for stream %u "
                "(%zu left in buffer %p, total %zu)\n",
@@ -568,16 +637,26 @@ static int on_data_chunk_recv(nghttp2_session *session, uint8_t flags,
                  ", stream %u\n",
                  len - nread, stream_id));
     data_s->easy_conn->proto.httpc.pause_stream_id = stream_id;
+
     return NGHTTP2_ERR_PAUSE;
   }
+
+  /* pause execution of nghttp2 if we received data for another handle
+     in order to process them first. */
+  if(conn->data != data_s) {
+    data_s->easy_conn->proto.httpc.pause_stream_id = stream_id;
+
+    return NGHTTP2_ERR_PAUSE;
+  }
+
   return 0;
 }
 
 static int before_frame_send(nghttp2_session *session,
                              const nghttp2_frame *frame,
                              void *userp)
 {
-  struct SessionHandle *data_s;
+  struct Curl_easy *data_s;
   (void)userp;
 
   data_s = nghttp2_session_get_stream_user_data(session, frame->hd.stream_id);
@@ -591,7 +670,7 @@ static int on_frame_send(nghttp2_session *session,
                          const nghttp2_frame *frame,
                          void *userp)
 {
-  struct SessionHandle *data_s;
+  struct Curl_easy *data_s;
   (void)userp;
 
   data_s = nghttp2_session_get_stream_user_data(session, frame->hd.stream_id);
@@ -605,7 +684,7 @@ static int on_frame_not_send(nghttp2_session *session,
                              const nghttp2_frame *frame,
                              int lib_error_code, void *userp)
 {
-  struct SessionHandle *data_s;
+  struct Curl_easy *data_s;
   (void)userp;
 
   data_s = nghttp2_session_get_stream_user_data(session, frame->hd.stream_id);
@@ -619,11 +698,11 @@ static int on_frame_not_send(nghttp2_session *session,
 static int on_stream_close(nghttp2_session *session, int32_t stream_id,
                            uint32_t error_code, void *userp)
 {
-  struct SessionHandle *data_s;
+  struct Curl_easy *data_s;
   struct HTTP *stream;
+  struct connectdata *conn = (struct connectdata *)userp;
   (void)session;
   (void)stream_id;
-  (void)userp;
 
   if(stream_id) {
     /* get the stream from the hash based on Stream ID, stream ID zero is for
@@ -634,14 +713,16 @@ static int on_stream_close(nghttp2_session *session, int32_t stream_id,
          decided to reject stream (e.g., PUSH_PROMISE). */
       return 0;
     }
-    DEBUGF(infof(data_s, "on_stream_close(), error_code = %d, stream %u\n",
-                 error_code, stream_id));
+    DEBUGF(infof(data_s, "on_stream_close(), %s (err %d), stream %u\n",
+                 Curl_http2_strerror(error_code), error_code, stream_id));
     stream = data_s->req.protop;
     if(!stream)
       return NGHTTP2_ERR_CALLBACK_FAILURE;
 
     stream->error_code = error_code;
     stream->closed = TRUE;
+    data_s->state.drain++;
+    conn->proto.httpc.drain_total++;
 
     /* remove the entry from the hash as the stream is now gone */
     nghttp2_session_set_stream_user_data(session, stream_id, 0);
@@ -653,13 +734,36 @@ static int on_stream_close(nghttp2_session *session, int32_t stream_id,
 static int on_begin_headers(nghttp2_session *session,
                             const nghttp2_frame *frame, void *userp)
 {
-  struct SessionHandle *data_s = NULL;
+  struct HTTP *stream;
+  struct Curl_easy *data_s = NULL;
   (void)userp;
 
   data_s = nghttp2_session_get_stream_user_data(session, frame->hd.stream_id);
-  if(data_s) {
-    DEBUGF(infof(data_s, "on_begin_headers() was called\n"));
+  if(!data_s) {
+    return 0;
+  }
+
+  DEBUGF(infof(data_s, "on_begin_headers() was called\n"));
+
+  if(frame->hd.type != NGHTTP2_HEADERS) {
+    return 0;
+  }
+
+  stream = data_s->req.protop;
+  if(!stream || !stream->bodystarted) {
+    return 0;
   }
+
+  /* This is trailer HEADERS started.  Allocate buffer for them. */
+  DEBUGF(infof(data_s, "trailer field started\n"));
+
+  assert(stream->trailer_recvbuf == NULL);
+
+  stream->trailer_recvbuf = Curl_add_buffer_init();
+  if(!stream->trailer_recvbuf) {
+    return NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;
+  }
+
   return 0;
 }
 
@@ -698,11 +802,10 @@ static int on_header(nghttp2_session *session, const nghttp2_frame *frame,
                      void *userp)
 {
   struct HTTP *stream;
-  struct SessionHandle *data_s;
+  struct Curl_easy *data_s;
   int32_t stream_id = frame->hd.stream_id;
-
+  struct connectdata *conn = (struct connectdata *)userp;
   (void)flags;
-  (void)userp;
 
   DEBUGASSERT(stream_id); /* should never be a zero stream ID here */
 
@@ -719,11 +822,6 @@ static int on_header(nghttp2_session *session, const nghttp2_frame *frame,
     return NGHTTP2_ERR_CALLBACK_FAILURE;
   }
 
-  if(stream->bodystarted)
-    /* Ignore trailer or HEADERS not mapped to HTTP semantics.  The
-       consequence is handled in on_frame_recv(). */
-    return 0;
-
   /* Store received PUSH_PROMISE headers to be used when the subsequent
      PUSH_PROMISE callback comes */
   if(frame->hd.type == NGHTTP2_PUSH_PROMISE) {
@@ -754,6 +852,23 @@ static int on_header(nghttp2_session *session, const nghttp2_frame *frame,
     return 0;
   }
 
+  if(stream->bodystarted) {
+    /* This is trailer fields. */
+    /* 3 is for ":" and "\r\n". */
+    uint32_t n = (uint32_t)(namelen + valuelen + 3);
+
+    DEBUGF(infof(data_s, "h2 trailer: %.*s: %.*s\n", namelen, name, valuelen,
+                 value));
+
+    Curl_add_buffer(stream->trailer_recvbuf, &n, sizeof(n));
+    Curl_add_buffer(stream->trailer_recvbuf, name, namelen);
+    Curl_add_buffer(stream->trailer_recvbuf, ": ", 2);
+    Curl_add_buffer(stream->trailer_recvbuf, value, valuelen);
+    Curl_add_buffer(stream->trailer_recvbuf, "\r\n\0", 3);
+
+    return 0;
+  }
+
   if(namelen == sizeof(":status") - 1 &&
      memcmp(":status", name, namelen) == 0) {
     /* nghttp2 guarantees :status is received first and only once, and
@@ -762,26 +877,29 @@ static int on_header(nghttp2_session *session, const nghttp2_frame *frame,
     stream->status_code = decode_status_code(value, valuelen);
     DEBUGASSERT(stream->status_code != -1);
 
-    Curl_add_buffer(stream->header_recvbuf, "HTTP/2.0 ", 9);
+    Curl_add_buffer(stream->header_recvbuf, "HTTP/2 ", 7);
     Curl_add_buffer(stream->header_recvbuf, value, valuelen);
-    Curl_add_buffer(stream->header_recvbuf, "\r\n", 2);
-    data_s->state.drain++;
-    Curl_expire(data_s, 1);
-
-    DEBUGF(infof(data_s, "h2 status: HTTP/2 %03d\n",
-                 stream->status_code));
+    /* the space character after the status code is mandatory */
+    Curl_add_buffer(stream->header_recvbuf, " \r\n", 3);
+    /* if we receive data for another handle, wake that up */
+    if(conn->data != data_s)
+      Curl_expire(data_s, 1);
+
+    DEBUGF(infof(data_s, "h2 status: HTTP/2 %03d (easy %p)\n",
+                 stream->status_code, data_s));
     return 0;
   }
 
   /* nghttp2 guarantees that namelen > 0, and :status was already
      received, and this is not pseudo-header field . */
   /* convert to a HTTP1-style header */
   Curl_add_buffer(stream->header_recvbuf, name, namelen);
-  Curl_add_buffer(stream->header_recvbuf, ":", 1);
+  Curl_add_buffer(stream->header_recvbuf, ": ", 2);
   Curl_add_buffer(stream->header_recvbuf, value, valuelen);
   Curl_add_buffer(stream->header_recvbuf, "\r\n", 2);
-  data_s->state.drain++;
-  Curl_expire(data_s, 1);
+  /* if we receive data for another handle, wake that up */
+  if(conn->data != data_s)
+    Curl_expire(data_s, 1);
 
   DEBUGF(infof(data_s, "h2 header: %.*s: %.*s\n", namelen, name, valuelen,
                value));
@@ -796,7 +914,7 @@ static ssize_t data_source_read_callback(nghttp2_session *session,
                                          nghttp2_data_source *source,
                                          void *userp)
 {
-  struct SessionHandle *data_s;
+  struct Curl_easy *data_s;
   struct HTTP *stream = NULL;
   size_t nread;
   (void)source;
@@ -848,6 +966,19 @@ static nghttp2_settings_entry settings[] = {
 
 #define H2_BUFSIZE 32768
 
+#ifdef NGHTTP2_HAS_ERROR_CALLBACK
+static int error_callback(nghttp2_session *session,
+                          const char *msg,
+                          size_t len,
+                          void *userp)
+{
+  struct connectdata *conn = (struct connectdata *)userp;
+  (void)session;
+  infof(conn->data, "http2 error: %.*s\n", len, msg);
+  return 0;
+}
+#endif
+
 /*
  * Initialize nghttp2 for a Curl connection
  */
@@ -897,6 +1028,8 @@ CURLcode Curl_http2_init(struct connectdata *conn)
     /* nghttp2_on_header_callback */
     nghttp2_session_callbacks_set_on_header_callback(callbacks, on_header);
 
+    nghttp2_session_callbacks_set_error_callback(callbacks, error_callback);
+
     /* The nghttp2 session is not yet setup, do it */
     rc = nghttp2_session_client_new(&conn->proto.httpc.h2, callbacks, conn);
 
@@ -906,25 +1039,11 @@ CURLcode Curl_http2_init(struct connectdata *conn)
       failf(conn->data, "Couldn't initialize nghttp2!");
       return CURLE_OUT_OF_MEMORY; /* most likely at least */
     }
-
-    if(rc) {
-      failf(conn->data, "Couldn't init stream hash!");
-      return CURLE_OUT_OF_MEMORY; /* most likely at least */
-    }
   }
   return CURLE_OK;
 }
 
 /*
- * Send a request using http2
- */
-CURLcode Curl_http2_send_request(struct connectdata *conn)
-{
-  (void)conn;
-  return CURLE_OK;
-}
-
-/*
  * Append headers to ask for a HTTP1.1 to HTTP2 upgrade.
  */
 CURLcode Curl_http2_request_upgrade(Curl_send_buffer *req,
@@ -969,26 +1088,187 @@ CURLcode Curl_http2_request_upgrade(Curl_send_buffer *req,
   return result;
 }
 
-static ssize_t http2_handle_stream_close(struct http_conn *httpc,
-                                         struct SessionHandle *data,
+/*
+ * Returns nonzero if current HTTP/2 session should be closed.
+ */
+static int should_close_session(struct http_conn *httpc) {
+  return httpc->drain_total == 0 && !nghttp2_session_want_read(httpc->h2) &&
+         !nghttp2_session_want_write(httpc->h2);
+}
+
+static int h2_session_send(struct Curl_easy *data,
+                           nghttp2_session *h2);
+
+/*
+ * h2_process_pending_input() processes pending input left in
+ * httpc->inbuf.  Then, call h2_session_send() to send pending data.
+ * This function returns 0 if it succeeds, or -1 and error code will
+ * be assigned to *err.
+ */
+static int h2_process_pending_input(struct Curl_easy *data,
+                                    struct http_conn *httpc,
+                                    CURLcode *err) {
+  ssize_t nread;
+  char *inbuf;
+  ssize_t rv;
+
+  nread = httpc->inbuflen - httpc->nread_inbuf;
+  inbuf = httpc->inbuf + httpc->nread_inbuf;
+
+  rv = nghttp2_session_mem_recv(httpc->h2, (const uint8_t *)inbuf, nread);
+  if(rv < 0) {
+    failf(data,
+          "h2_process_pending_input: nghttp2_session_mem_recv() returned "
+          "%d:%s\n", rv, nghttp2_strerror((int)rv));
+    *err = CURLE_RECV_ERROR;
+    return -1;
+  }
+
+  if(nread == rv) {
+    DEBUGF(infof(data,
+                 "h2_process_pending_input: All data in connection buffer "
+                 "processed\n"));
+    httpc->inbuflen = 0;
+    httpc->nread_inbuf = 0;
+  }
+  else {
+    httpc->nread_inbuf += rv;
+    DEBUGF(infof(data,
+                 "h2_process_pending_input: %zu bytes left in connection "
+                 "buffer\n",
+                 httpc->inbuflen - httpc->nread_inbuf));
+  }
+
+  rv = h2_session_send(data, httpc->h2);
+  if(rv != 0) {
+    *err = CURLE_SEND_ERROR;
+    return -1;
+  }
+
+  if(should_close_session(httpc)) {
+    DEBUGF(infof(data,
+                 "h2_process_pending_input: nothing to do in this session\n"));
+    *err = CURLE_HTTP2;
+    return -1;
+  }
+
+  return 0;
+}
+
+static ssize_t http2_handle_stream_close(struct connectdata *conn,
+                                         struct Curl_easy *data,
                                          struct HTTP *stream, CURLcode *err) {
+  char *trailer_pos, *trailer_end;
+  CURLcode result;
+  struct http_conn *httpc = &conn->proto.httpc;
+
   if(httpc->pause_stream_id == stream->stream_id) {
     httpc->pause_stream_id = 0;
   }
+
+  DEBUGASSERT(httpc->drain_total >= data->state.drain);
+  httpc->drain_total -= data->state.drain;
+  data->state.drain = 0;
+
+  if(httpc->pause_stream_id == 0) {
+    if(h2_process_pending_input(data, httpc, err) != 0) {
+      return -1;
+    }
+  }
+
+  DEBUGASSERT(data->state.drain == 0);
+
   /* Reset to FALSE to prevent infinite loop in readwrite_data
    function. */
   stream->closed = FALSE;
   if(stream->error_code != NGHTTP2_NO_ERROR) {
-    failf(data, "HTTP/2 stream %u was not closed cleanly: error_code = %d",
-          stream->stream_id, stream->error_code);
-    *err = CURLE_HTTP2;
+    failf(data, "HTTP/2 stream %u was not closed cleanly: %s (err %d)",
+          stream->stream_id, Curl_http2_strerror(stream->error_code),
+          stream->error_code);
+    *err = CURLE_HTTP2_STREAM;
+    return -1;
+  }
+
+  if(!stream->bodystarted) {
+    failf(data, "HTTP/2 stream %u was closed cleanly, but before getting "
+          " all response header fields, teated as error",
+          stream->stream_id);
+    *err = CURLE_HTTP2_STREAM;
     return -1;
   }
+
+  if(stream->trailer_recvbuf && stream->trailer_recvbuf->buffer) {
+    trailer_pos = stream->trailer_recvbuf->buffer;
+    trailer_end = trailer_pos + stream->trailer_recvbuf->size_used;
+
+    for(; trailer_pos < trailer_end;) {
+      uint32_t n;
+      memcpy(&n, trailer_pos, sizeof(n));
+      trailer_pos += sizeof(n);
+
+      result = Curl_client_write(conn, CLIENTWRITE_HEADER, trailer_pos, n);
+      if(result) {
+        *err = result;
+        return -1;
+      }
+
+      trailer_pos += n + 1;
+    }
+  }
+
   DEBUGF(infof(data, "http2_recv returns 0, http2_handle_stream_close\n"));
   return 0;
 }
 
 /*
+ * h2_pri_spec() fills in the pri_spec struct, used by nghttp2 to send weight
+ * and dependency to the peer. It also stores the updated values in the state
+ * struct.
+ */
+
+static void h2_pri_spec(struct Curl_easy *data,
+                        nghttp2_priority_spec *pri_spec)
+{
+  struct HTTP *depstream = (data->set.stream_depends_on?
+                            data->set.stream_depends_on->req.protop:NULL);
+  int32_t depstream_id = depstream? depstream->stream_id:0;
+  nghttp2_priority_spec_init(pri_spec, depstream_id, data->set.stream_weight,
+                             data->set.stream_depends_e);
+  data->state.stream_weight = data->set.stream_weight;
+  data->state.stream_depends_e = data->set.stream_depends_e;
+  data->state.stream_depends_on = data->set.stream_depends_on;
+}
+
+/*
+ * h2_session_send() checks if there's been an update in the priority /
+ * dependency settings and if so it submits a PRIORITY frame with the updated
+ * info.
+ */
+static int h2_session_send(struct Curl_easy *data,
+                           nghttp2_session *h2)
+{
+  struct HTTP *stream = data->req.protop;
+  if((data->set.stream_weight != data->state.stream_weight) ||
+     (data->set.stream_depends_e != data->state.stream_depends_e) ||
+     (data->set.stream_depends_on != data->state.stream_depends_on) ) {
+    /* send new weight and/or dependency */
+    nghttp2_priority_spec pri_spec;
+    int rv;
+
+    h2_pri_spec(data, &pri_spec);
+
+    DEBUGF(infof(data, "Queuing PRIORITY on stream %u (easy %p)\n",
+                 stream->stream_id, data));
+    rv = nghttp2_submit_priority(h2, NGHTTP2_FLAG_NONE, stream->stream_id,
+                                 &pri_spec);
+    if(rv)
+      return rv;
+  }
+
+  return nghttp2_session_send(h2);
+}
+
+/*
  * If the read would block (EWOULDBLOCK) we return -1. Otherwise we return
  * a regular CURLcode value.
  */
@@ -999,17 +1279,16 @@ static ssize_t http2_recv(struct connectdata *conn, int sockindex,
   ssize_t rv;
   ssize_t nread;
   struct http_conn *httpc = &conn->proto.httpc;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct HTTP *stream = data->req.protop;
 
   (void)sockindex; /* we always do HTTP2 on sockindex 0 */
 
-  /* If stream is closed, return 0 to signal the http routine to close
-     the connection.  We need to handle stream closure here,
-     otherwise, we may be going to read from underlying connection,
-     and gets EAGAIN, and we will get stuck there. */
-  if(stream->memlen == 0 && stream->closed) {
-    return http2_handle_stream_close(httpc, data, stream, err);
+  if(should_close_session(httpc)) {
+    DEBUGF(infof(data,
+                 "http2_recv: nothing to do in this session\n"));
+    *err = CURLE_HTTP2;
+    return -1;
   }
 
   /* Nullify here because we call nghttp2_session_send() and they
@@ -1018,7 +1297,7 @@ static ssize_t http2_recv(struct connectdata *conn, int sockindex,
   stream->upload_len = 0;
 
   /*
-   * At this point 'stream' is just in the SessionHandle the connection
+   * At this point 'stream' is just in the Curl_easy the connection
    * identifies as its owner at this time.
    */
 
@@ -1032,13 +1311,13 @@ static ssize_t http2_recv(struct connectdata *conn, int sockindex,
            ncopy);
     stream->nread_header_recvbuf += ncopy;
 
-    infof(data, "http2_recv: Got %d bytes from header_recvbuf\n",
-          (int)ncopy);
+    DEBUGF(infof(data, "http2_recv: Got %d bytes from header_recvbuf\n",
+                 (int)ncopy));
     return ncopy;
   }
 
-  infof(data, "http2_recv: %d bytes buffer at %p (stream %u)\n",
-        len, mem, stream->stream_id);
+  DEBUGF(infof(data, "http2_recv: easy %p (stream %u)\n",
+               data, stream->stream_id));
 
   if((data->state.drain) && stream->memlen) {
     DEBUGF(infof(data, "http2_recv: DRAIN %zu bytes stream %u!! (%p => %p)\n",
@@ -1051,8 +1330,18 @@ static ssize_t http2_recv(struct connectdata *conn, int sockindex,
       stream->len = len - stream->memlen;
       stream->mem = mem;
     }
+    if(httpc->pause_stream_id == stream->stream_id && !stream->pausedata) {
+      /* We have paused nghttp2, but we have no pause data (see
+         on_data_chunk_recv). */
+      httpc->pause_stream_id = 0;
+      if(h2_process_pending_input(data, httpc, &result) != 0) {
+        *err = result;
+        return -1;
+      }
+    }
   }
   else if(stream->pausedata) {
+    DEBUGASSERT(httpc->pause_stream_id == stream->stream_id);
     nread = MIN(len, stream->pauselen);
     memcpy(mem, stream->pausedata, nread);
 
@@ -1067,9 +1356,21 @@ static ssize_t http2_recv(struct connectdata *conn, int sockindex,
 
       stream->pausedata = NULL;
       stream->pauselen = 0;
+
+      /* When NGHTTP2_ERR_PAUSE is returned from
+         data_source_read_callback, we might not process DATA frame
+         fully.  Calling nghttp2_session_mem_recv() again will
+         continue to process DATA frame, but if there is no incoming
+         frames, then we have to call it again with 0-length data.
+         Without this, on_stream_close callback will not be called,
+         and stream could be hanged. */
+      if(h2_process_pending_input(data, httpc, &result) != 0) {
+        *err = result;
+        return -1;
+      }
     }
-    infof(data, "http2_recv: returns unpaused %zd bytes on stream %u\n",
-          nread, stream->stream_id);
+    DEBUGF(infof(data, "http2_recv: returns unpaused %zd bytes on stream %u\n",
+                 nread, stream->stream_id));
     return nread;
   }
   else if(httpc->pause_stream_id) {
@@ -1096,15 +1397,15 @@ static ssize_t http2_recv(struct connectdata *conn, int sockindex,
       nread = ((Curl_recv *)httpc->recv_underlying)(
           conn, FIRSTSOCKET, httpc->inbuf, H2_BUFSIZE, &result);
 
-      if(result == CURLE_AGAIN) {
-        *err = result;
-        return -1;
-      }
-
       if(nread == -1) {
-        failf(data, "Failed receiving HTTP2 data");
+        if(result != CURLE_AGAIN)
+          failf(data, "Failed receiving HTTP2 data");
+        else if(stream->closed)
+          /* received when the stream was already closed! */
+          return http2_handle_stream_close(conn, data, stream, err);
+
         *err = result;
-        return 0;
+        return -1;
       }
 
       if(nread == 0) {
@@ -1146,16 +1447,22 @@ static ssize_t http2_recv(struct connectdata *conn, int sockindex,
     }
     /* Always send pending frames in nghttp2 session, because
        nghttp2_session_mem_recv() may queue new frame */
-    rv = nghttp2_session_send(httpc->h2);
+    rv = h2_session_send(data, httpc->h2);
     if(rv != 0) {
       *err = CURLE_SEND_ERROR;
       return 0;
     }
+
+    if(should_close_session(httpc)) {
+      DEBUGF(infof(data, "http2_recv: nothing to do in this session\n"));
+      *err = CURLE_HTTP2;
+      return -1;
+    }
   }
   if(stream->memlen) {
     ssize_t retlen = stream->memlen;
-    infof(data, "http2_recv: returns %zd for stream %u\n",
-          retlen, stream->stream_id);
+    DEBUGF(infof(data, "http2_recv: returns %zd for stream %u\n",
+                 retlen, stream->stream_id));
     stream->memlen = 0;
 
     if(httpc->pause_stream_id == stream->stream_id) {
@@ -1164,15 +1471,18 @@ static ssize_t http2_recv(struct connectdata *conn, int sockindex,
       DEBUGF(infof(data, "Data returned for PAUSED stream %u\n",
                    stream->stream_id));
     }
-    else
+    else if(!stream->closed) {
+      DEBUGASSERT(httpc->drain_total >= data->state.drain);
+      httpc->drain_total -= data->state.drain;
       data->state.drain = 0; /* this stream is hereby drained */
+    }
 
     return retlen;
   }
   /* If stream is closed, return 0 to signal the http routine to close
      the connection */
   if(stream->closed) {
-    return http2_handle_stream_close(httpc, data, stream, err);
+    return http2_handle_stream_close(conn, data, stream, err);
   }
   *err = CURLE_AGAIN;
   DEBUGF(infof(data, "http2_recv returns AGAIN for stream %u\n",
@@ -1184,6 +1494,9 @@ static ssize_t http2_recv(struct connectdata *conn, int sockindex,
    field list. */
 #define AUTHORITY_DST_IDX 3
 
+#define HEADER_OVERFLOW(x) \
+  (x.namelen > (uint16_t)-1 || x.valuelen > (uint16_t)-1 - x.namelen)
+
 /* return number of received (decrypted) bytes */
 static ssize_t http2_send(struct connectdata *conn, int sockindex,
                           const void *mem, size_t len, CURLcode *err)
@@ -1196,15 +1509,16 @@ static ssize_t http2_send(struct connectdata *conn, int sockindex,
   int rv;
   struct http_conn *httpc = &conn->proto.httpc;
   struct HTTP *stream = conn->data->req.protop;
-  nghttp2_nv *nva;
+  nghttp2_nv *nva = NULL;
   size_t nheader;
   size_t i;
   size_t authority_idx;
   char *hdbuf = (char*)mem;
-  char *end;
+  char *end, *line_end;
   nghttp2_data_provider data_prd;
   int32_t stream_id;
   nghttp2_session *h2 = httpc->h2;
+  nghttp2_priority_spec pri_spec;
 
   (void)sockindex;
 
@@ -1216,7 +1530,7 @@ static ssize_t http2_send(struct connectdata *conn, int sockindex,
     stream->upload_mem = mem;
     stream->upload_len = len;
     nghttp2_session_resume_data(h2, stream->stream_id);
-    rv = nghttp2_session_send(h2);
+    rv = h2_session_send(conn->data, h2);
     if(nghttp2_is_fatal(rv)) {
       *err = CURLE_SEND_ERROR;
       return -1;
@@ -1228,6 +1542,12 @@ static ssize_t http2_send(struct connectdata *conn, int sockindex,
     stream->upload_mem = NULL;
     stream->upload_len = 0;
 
+    if(should_close_session(httpc)) {
+      DEBUGF(infof(conn->data, "http2_send: nothing to do in this session\n"));
+      *err = CURLE_HTTP2;
+      return -1;
+    }
+
     if(stream->upload_left) {
       /* we are sure that we have more data to send here.  Calling the
          following API will make nghttp2_session_want_write() return
@@ -1245,12 +1565,16 @@ static ssize_t http2_send(struct connectdata *conn, int sockindex,
   /* Here, we assume the curl http code generate *correct* HTTP header
      field block */
   nheader = 0;
-  for(i = 0; i < len; ++i) {
-    if(hdbuf[i] == 0x0a) {
+  for(i = 1; i < len; ++i) {
+    if(hdbuf[i] == '\n' && hdbuf[i - 1] == '\r') {
       ++nheader;
+      ++i;
     }
   }
-  /* We counted additional 2 \n in the first and last line. We need 3
+  if(nheader < 2)
+    goto fail;
+
+  /* We counted additional 2 \r\n in the first and last line. We need 3
      new headers: :method, :path and :scheme. Therefore we need one
      more space. */
   nheader += 1;
@@ -1259,81 +1583,133 @@ static ssize_t http2_send(struct connectdata *conn, int sockindex,
     *err = CURLE_OUT_OF_MEMORY;
     return -1;
   }
+
   /* Extract :method, :path from request line */
-  end = strchr(hdbuf, ' ');
-  if(!end)
+  line_end = strstr(hdbuf, "\r\n");
+
+  /* Method does not contain spaces */
+  end = memchr(hdbuf, ' ', line_end - hdbuf);
+  if(!end || end == hdbuf)
     goto fail;
   nva[0].name = (unsigned char *)":method";
-  nva[0].namelen = (uint16_t)strlen((char *)nva[0].name);
+  nva[0].namelen = strlen((char *)nva[0].name);
   nva[0].value = (unsigned char *)hdbuf;
-  nva[0].valuelen = (uint16_t)(end - hdbuf);
+  nva[0].valuelen = (size_t)(end - hdbuf);
   nva[0].flags = NGHTTP2_NV_FLAG_NONE;
+  if(HEADER_OVERFLOW(nva[0])) {
+    failf(conn->data, "Failed sending HTTP request: Header overflow");
+    goto fail;
+  }
 
   hdbuf = end + 1;
 
-  end = strchr(hdbuf, ' ');
-  if(!end)
+  /* Path may contain spaces so scan backwards */
+  end = NULL;
+  for(i = (size_t)(line_end - hdbuf); i; --i) {
+    if(hdbuf[i - 1] == ' ') {
+      end = &hdbuf[i - 1];
+      break;
+    }
+  }
+  if(!end || end == hdbuf)
     goto fail;
   nva[1].name = (unsigned char *)":path";
-  nva[1].namelen = (uint16_t)strlen((char *)nva[1].name);
+  nva[1].namelen = strlen((char *)nva[1].name);
   nva[1].value = (unsigned char *)hdbuf;
-  nva[1].valuelen = (uint16_t)(end - hdbuf);
+  nva[1].valuelen = (size_t)(end - hdbuf);
   nva[1].flags = NGHTTP2_NV_FLAG_NONE;
+  if(HEADER_OVERFLOW(nva[1])) {
+    failf(conn->data, "Failed sending HTTP request: Header overflow");
+    goto fail;
+  }
+
+  hdbuf = end + 1;
 
+  end = line_end;
   nva[2].name = (unsigned char *)":scheme";
-  nva[2].namelen = (uint16_t)strlen((char *)nva[2].name);
+  nva[2].namelen = strlen((char *)nva[2].name);
   if(conn->handler->flags & PROTOPT_SSL)
     nva[2].value = (unsigned char *)"https";
   else
     nva[2].value = (unsigned char *)"http";
-  nva[2].valuelen = (uint16_t)strlen((char *)nva[2].value);
+  nva[2].valuelen = strlen((char *)nva[2].value);
   nva[2].flags = NGHTTP2_NV_FLAG_NONE;
-
-  hdbuf = strchr(hdbuf, 0x0a);
-  if(!hdbuf)
+  if(HEADER_OVERFLOW(nva[2])) {
+    failf(conn->data, "Failed sending HTTP request: Header overflow");
     goto fail;
-  ++hdbuf;
+  }
 
   authority_idx = 0;
+  i = 3;
+  while(i < nheader) {
+    size_t hlen;
+    int skip = 0;
+
+    hdbuf = line_end + 2;
+
+    line_end = strstr(hdbuf, "\r\n");
+    if(line_end == hdbuf)
+      goto fail;
+
+    /* header continuation lines are not supported */
+    if(*hdbuf == ' ' || *hdbuf == '\t')
+      goto fail;
 
-  for(i = 3; i < nheader; ++i) {
-    end = strchr(hdbuf, ':');
-    if(!end)
+    for(end = hdbuf; end < line_end && *end != ':'; ++end)
+      ;
+    if(end == hdbuf || end == line_end)
       goto fail;
-    if(end - hdbuf == 4 && Curl_raw_nequal("host", hdbuf, 4)) {
+    hlen = end - hdbuf;
+
+    if(hlen == 10 && Curl_raw_nequal("connection", hdbuf, 10)) {
+      /* skip Connection: headers! */
+      skip = 1;
+      --nheader;
+    }
+    else if(hlen == 4 && Curl_raw_nequal("host", hdbuf, 4)) {
       authority_idx = i;
       nva[i].name = (unsigned char *)":authority";
-      nva[i].namelen = (uint16_t)strlen((char *)nva[i].name);
+      nva[i].namelen = strlen((char *)nva[i].name);
     }
     else {
       nva[i].name = (unsigned char *)hdbuf;
-      nva[i].namelen = (uint16_t)(end - hdbuf);
+      nva[i].namelen = (size_t)(end - hdbuf);
     }
     hdbuf = end + 1;
-    for(; *hdbuf == ' '; ++hdbuf);
-    end = strchr(hdbuf, 0x0d);
-    if(!end)
-      goto fail;
-    nva[i].value = (unsigned char *)hdbuf;
-    nva[i].valuelen = (uint16_t)(end - hdbuf);
-    nva[i].flags = NGHTTP2_NV_FLAG_NONE;
-
-    hdbuf = end + 2;
-    /* Inspect Content-Length header field and retrieve the request
-       entity length so that we can set END_STREAM to the last DATA
-       frame. */
-    if(nva[i].namelen == 14 &&
-       Curl_raw_nequal("content-length", (char*)nva[i].name, 14)) {
-      size_t j;
-      stream->upload_left = 0;
-      for(j = 0; j < nva[i].valuelen; ++j) {
-        stream->upload_left *= 10;
-        stream->upload_left += nva[i].value[j] - '0';
+    while(*hdbuf == ' ' || *hdbuf == '\t')
+      ++hdbuf;
+    end = line_end;
+    if(!skip) {
+      nva[i].value = (unsigned char *)hdbuf;
+      nva[i].valuelen = (size_t)(end - hdbuf);
+      nva[i].flags = NGHTTP2_NV_FLAG_NONE;
+      if(HEADER_OVERFLOW(nva[i])) {
+        failf(conn->data, "Failed sending HTTP request: Header overflow");
+        goto fail;
       }
-      DEBUGF(infof(conn->data,
-                   "request content-length=%"
-                   CURL_FORMAT_CURL_OFF_T
-                   "\n", stream->upload_left));
+      /* Inspect Content-Length header field and retrieve the request
+         entity length so that we can set END_STREAM to the last DATA
+         frame. */
+      if(nva[i].namelen == 14 &&
+         Curl_raw_nequal("content-length", (char*)nva[i].name, 14)) {
+        size_t j;
+        stream->upload_left = 0;
+        if(!nva[i].valuelen)
+          goto fail;
+        for(j = 0; j < nva[i].valuelen; ++j) {
+          if(nva[i].value[j] < '0' || nva[i].value[j] > '9')
+            goto fail;
+          if(stream->upload_left >= CURL_OFF_T_MAX / 10)
+            goto fail;
+          stream->upload_left *= 10;
+          stream->upload_left += nva[i].value[j] - '0';
+        }
+        DEBUGF(infof(conn->data,
+                     "request content-length=%"
+                     CURL_FORMAT_CURL_OFF_T
+                     "\n", stream->upload_left));
+      }
+      ++i;
     }
   }
 
@@ -1346,17 +1722,42 @@ static ssize_t http2_send(struct connectdata *conn, int sockindex,
     nva[i] = authority;
   }
 
+  /* Warn stream may be rejected if cumulative length of headers is too large.
+     It appears nghttp2 will not send a header frame larger than 64KB. */
+  {
+    size_t acc = 0;
+    const size_t max_acc = 60000;  /* <64KB to account for some overhead */
+
+    for(i = 0; i < nheader; ++i) {
+      if(nva[i].namelen > max_acc - acc)
+        break;
+      acc += nva[i].namelen;
+
+      if(nva[i].valuelen > max_acc - acc)
+        break;
+      acc += nva[i].valuelen;
+    }
+
+    if(i != nheader) {
+      infof(conn->data, "http2_send: Warning: The cumulative length of all "
+                        "headers exceeds %zu bytes and that could cause the "
+                        "stream to be rejected.\n", max_acc);
+    }
+  }
+
+  h2_pri_spec(conn->data, &pri_spec);
+
   switch(conn->data->set.httpreq) {
   case HTTPREQ_POST:
   case HTTPREQ_POST_FORM:
   case HTTPREQ_PUT:
     data_prd.read_callback = data_source_read_callback;
     data_prd.source.ptr = NULL;
-    stream_id = nghttp2_submit_request(h2, NULL, nva, nheader,
+    stream_id = nghttp2_submit_request(h2, &pri_spec, nva, nheader,
                                        &data_prd, conn->data);
     break;
   default:
-    stream_id = nghttp2_submit_request(h2, NULL, nva, nheader,
+    stream_id = nghttp2_submit_request(h2, &pri_spec, nva, nheader,
                                        NULL, conn->data);
   }
 
@@ -1372,13 +1773,21 @@ static ssize_t http2_send(struct connectdata *conn, int sockindex,
         stream_id, conn->data);
   stream->stream_id = stream_id;
 
+  /* this does not call h2_session_send() since there can not have been any
+   * priority upodate since the nghttp2_submit_request() call above */
   rv = nghttp2_session_send(h2);
 
   if(rv != 0) {
     *err = CURLE_SEND_ERROR;
     return -1;
   }
 
+  if(should_close_session(httpc)) {
+    DEBUGF(infof(conn->data, "http2_send: nothing to do in this session\n"));
+    *err = CURLE_HTTP2;
+    return -1;
+  }
+
   if(stream->stream_id != -1) {
     /* If whole HEADERS frame was sent off to the underlying socket,
        the nghttp2 library calls data_source_read_callback. But only
@@ -1393,7 +1802,7 @@ static ssize_t http2_send(struct connectdata *conn, int sockindex,
 
   return len;
 
-  fail:
+fail:
   free(nva);
   *err = CURLE_SEND_ERROR;
   return -1;
@@ -1432,6 +1841,7 @@ CURLcode Curl_http2_setup(struct connectdata *conn)
   httpc->nread_inbuf = 0;
 
   httpc->pause_stream_id = 0;
+  httpc->drain_total = 0;
 
   conn->bits.multiplex = TRUE; /* at least potentially multiplexed */
   conn->httpversion = 20;
@@ -1440,6 +1850,10 @@ CURLcode Curl_http2_setup(struct connectdata *conn)
   infof(conn->data, "Connection state changed (HTTP/2 confirmed)\n");
   Curl_multi_connchanged(conn->data->multi);
 
+  /* switch on TCP_NODELAY as we need to send off packets without delay for
+     maximum throughput */
+  Curl_tcpnodelay(conn, conn->sock[FIRSTSOCKET]);
+
   return CURLE_OK;
 }
 
@@ -1450,7 +1864,7 @@ CURLcode Curl_http2_switched(struct connectdata *conn,
   struct http_conn *httpc = &conn->proto.httpc;
   int rv;
   ssize_t nproc;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct HTTP *stream = conn->data->req.protop;
 
   result = Curl_http2_setup(conn);
@@ -1527,14 +1941,20 @@ CURLcode Curl_http2_switched(struct connectdata *conn,
   }
 
   /* Try to send some frames since we may read SETTINGS already. */
-  rv = nghttp2_session_send(httpc->h2);
+  rv = h2_session_send(data, httpc->h2);
 
   if(rv != 0) {
     failf(data, "nghttp2_session_send() failed: %s(%d)",
           nghttp2_strerror(rv), rv);
     return CURLE_HTTP2;
   }
 
+  if(should_close_session(httpc)) {
+    DEBUGF(infof(data,
+                 "nghttp2_session_send(): nothing to do in this session\n"));
+    return CURLE_HTTP2;
+  }
+
   return CURLE_OK;
 }
 