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
@@ -31,10 +31,11 @@
 #include "ssh.h"
 #include "multiif.h"
 #include "non-ascii.h"
-#include "curl_printf.h"
 #include "strerror.h"
+#include "select.h"
 
-/* The last #include files should be: */
+/* The last 3 #include files should be in this order */
+#include "curl_printf.h"
 #include "curl_memory.h"
 #include "memdebug.h"
 
@@ -45,7 +46,7 @@
  * blocks of data.  Remaining, bare CRs are changed to LFs.  The possibly new
  * size of the data is returned.
  */
-static size_t convert_lineends(struct SessionHandle *data,
+static size_t convert_lineends(struct Curl_easy *data,
                                char *startPtr, size_t size)
 {
   char *inPtr, *outPtr;
@@ -120,9 +121,93 @@ static size_t convert_lineends(struct SessionHandle *data,
 }
 #endif /* CURL_DO_LINEEND_CONV */
 
+#ifdef USE_RECV_BEFORE_SEND_WORKAROUND
+static void pre_receive_plain(struct connectdata *conn, int num)
+{
+  const curl_socket_t sockfd = conn->sock[num];
+  struct postponed_data * const psnd = &(conn->postponed[num]);
+  size_t bytestorecv = psnd->allocated_size - psnd->recv_size;
+  /* WinSock will destroy unread received data if send() is
+     failed.
+     To avoid lossage of received data, recv() must be
+     performed before every send() if any incoming data is
+     available. However, skip this, if buffer is already full. */
+  if((conn->handler->protocol&PROTO_FAMILY_HTTP) != 0 &&
+     conn->recv[num] == Curl_recv_plain &&
+     (!psnd->buffer || bytestorecv)) {
+    const int readymask = Curl_socket_check(sockfd, CURL_SOCKET_BAD,
+                                            CURL_SOCKET_BAD, 0);
+    if(readymask != -1 && (readymask & CURL_CSELECT_IN) != 0) {
+      /* Have some incoming data */
+      if(!psnd->buffer) {
+        /* Use buffer double default size for intermediate buffer */
+        psnd->allocated_size = 2 * BUFSIZE;
+        psnd->buffer = malloc(psnd->allocated_size);
+        psnd->recv_size = 0;
+        psnd->recv_processed = 0;
+#ifdef DEBUGBUILD
+        psnd->bindsock = sockfd; /* Used only for DEBUGASSERT */
+#endif /* DEBUGBUILD */
+        bytestorecv = psnd->allocated_size;
+      }
+      if(psnd->buffer) {
+        ssize_t recvedbytes;
+        DEBUGASSERT(psnd->bindsock == sockfd);
+        recvedbytes = sread(sockfd, psnd->buffer + psnd->recv_size,
+                            bytestorecv);
+        if(recvedbytes > 0)
+          psnd->recv_size += recvedbytes;
+      }
+      else
+        psnd->allocated_size = 0;
+    }
+  }
+}
+
+static ssize_t get_pre_recved(struct connectdata *conn, int num, char *buf,
+                              size_t len)
+{
+  struct postponed_data * const psnd = &(conn->postponed[num]);
+  size_t copysize;
+  if(!psnd->buffer)
+    return 0;
+
+  DEBUGASSERT(psnd->allocated_size > 0);
+  DEBUGASSERT(psnd->recv_size <= psnd->allocated_size);
+  DEBUGASSERT(psnd->recv_processed <= psnd->recv_size);
+  /* Check and process data that already received and storied in internal
+     intermediate buffer */
+  if(psnd->recv_size > psnd->recv_processed) {
+    DEBUGASSERT(psnd->bindsock == conn->sock[num]);
+    copysize = CURLMIN(len, psnd->recv_size - psnd->recv_processed);
+    memcpy(buf, psnd->buffer + psnd->recv_processed, copysize);
+    psnd->recv_processed += copysize;
+  }
+  else
+    copysize = 0; /* buffer was allocated, but nothing was received */
+
+  /* Free intermediate buffer if it has no unprocessed data */
+  if(psnd->recv_processed == psnd->recv_size) {
+    free(psnd->buffer);
+    psnd->buffer = NULL;
+    psnd->allocated_size = 0;
+    psnd->recv_size = 0;
+    psnd->recv_processed = 0;
+#ifdef DEBUGBUILD
+    psnd->bindsock = CURL_SOCKET_BAD;
+#endif /* DEBUGBUILD */
+  }
+  return (ssize_t)copysize;
+}
+#else  /* ! USE_RECV_BEFORE_SEND_WORKAROUND */
+/* Use "do-nothing" macros instead of functions when workaround not used */
+#define pre_receive_plain(c,n) do {} WHILE_FALSE
+#define get_pre_recved(c,n,b,l) 0
+#endif /* ! USE_RECV_BEFORE_SEND_WORKAROUND */
+
 /* Curl_infof() is for info message along the way */
 
-void Curl_infof(struct SessionHandle *data, const char *fmt, ...)
+void Curl_infof(struct Curl_easy *data, const char *fmt, ...)
 {
   if(data && data->set.verbose) {
     va_list ap;
@@ -140,7 +225,7 @@ void Curl_infof(struct SessionHandle *data, const char *fmt, ...)
  * The message SHALL NOT include any LF or CR.
  */
 
-void Curl_failf(struct SessionHandle *data, const char *fmt, ...)
+void Curl_failf(struct Curl_easy *data, const char *fmt, ...)
 {
   va_list ap;
   size_t len;
@@ -168,7 +253,7 @@ void Curl_failf(struct SessionHandle *data, const char *fmt, ...)
 CURLcode Curl_sendf(curl_socket_t sockfd, struct connectdata *conn,
                     const char *fmt, ...)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   ssize_t bytes_written;
   size_t write_len;
   CURLcode result = CURLE_OK;
@@ -254,7 +339,23 @@ ssize_t Curl_send_plain(struct connectdata *conn, int num,
                         const void *mem, size_t len, CURLcode *code)
 {
   curl_socket_t sockfd = conn->sock[num];
-  ssize_t bytes_written = swrite(sockfd, mem, len);
+  ssize_t bytes_written;
+  /* WinSock will destroy unread received data if send() is
+     failed.
+     To avoid lossage of received data, recv() must be
+     performed before every send() if any incoming data is
+     available. */
+  pre_receive_plain(conn, num);
+
+#ifdef MSG_FASTOPEN /* Linux */
+  if(conn->bits.tcp_fastopen) {
+    bytes_written = sendto(sockfd, mem, len, MSG_FASTOPEN,
+                           conn->ip_addr->ai_addr, conn->ip_addr->ai_addrlen);
+    conn->bits.tcp_fastopen = FALSE;
+  }
+  else
+#endif
+    bytes_written = swrite(sockfd, mem, len);
 
   *code = CURLE_OK;
   if(-1 == bytes_written) {
@@ -268,7 +369,8 @@ ssize_t Curl_send_plain(struct connectdata *conn, int num,
       /* errno may be EWOULDBLOCK or on some systems EAGAIN when it returned
          due to its inability to send off data without blocking. We therefor
          treat both error codes the same here */
-      (EWOULDBLOCK == err) || (EAGAIN == err) || (EINTR == err)
+      (EWOULDBLOCK == err) || (EAGAIN == err) || (EINTR == err) ||
+      (EINPROGRESS == err)
 #endif
       ) {
       /* this is just a case of EWOULDBLOCK */
@@ -311,7 +413,16 @@ ssize_t Curl_recv_plain(struct connectdata *conn, int num, char *buf,
                         size_t len, CURLcode *code)
 {
   curl_socket_t sockfd = conn->sock[num];
-  ssize_t nread = sread(sockfd, buf, len);
+  ssize_t nread;
+  /* Check and return data that already received and storied in internal
+     intermediate buffer */
+  nread = get_pre_recved(conn, num, buf, len);
+  if(nread > 0) {
+    *code = CURLE_OK;
+    return nread;
+  }
+
+  nread = sread(sockfd, buf, len);
 
   *code = CURLE_OK;
   if(-1 == nread) {
@@ -341,7 +452,7 @@ ssize_t Curl_recv_plain(struct connectdata *conn, int num, char *buf,
   return nread;
 }
 
-static CURLcode pausewrite(struct SessionHandle *data,
+static CURLcode pausewrite(struct Curl_easy *data,
                            int type, /* what type of data */
                            const char *ptr,
                            size_t len)
@@ -380,7 +491,7 @@ CURLcode Curl_client_chop_write(struct connectdata *conn,
                                 char * ptr,
                                 size_t len)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   curl_write_callback writeheader = NULL;
   curl_write_callback writebody = NULL;
 
@@ -487,7 +598,7 @@ CURLcode Curl_client_write(struct connectdata *conn,
                            char *ptr,
                            size_t len)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
 
   if(0 == len)
     len = strlen(ptr);
@@ -520,11 +631,13 @@ CURLcode Curl_read_plain(curl_socket_t sockfd,
 
   if(-1 == nread) {
     int err = SOCKERRNO;
+    int return_error;
 #ifdef USE_WINSOCK
-    if(WSAEWOULDBLOCK == err)
+    return_error = WSAEWOULDBLOCK == err;
 #else
-    if((EWOULDBLOCK == err) || (EAGAIN == err) || (EINTR == err))
+    return_error = EWOULDBLOCK == err || EAGAIN == err || EINTR == err;
 #endif
+    if(return_error)
       return CURLE_AGAIN;
     else
       return CURLE_RECV_ERROR;
@@ -551,7 +664,10 @@ CURLcode Curl_read(struct connectdata *conn, /* connection data */
   ssize_t nread = 0;
   size_t bytesfromsocket = 0;
   char *buffertofill = NULL;
-  bool pipelining = Curl_pipeline_wanted(conn->data->multi, CURLPIPE_HTTP1);
+
+  /* if HTTP/1 pipelining is both wanted and possible */
+  bool pipelining = Curl_pipeline_wanted(conn->data->multi, CURLPIPE_HTTP1) &&
+    (conn->bundle->multiuse == BUNDLE_PIPELINING);
 
   /* Set 'num' to 0 or 1, depending on which socket that has been sent here.
      If it is the second socket, we set num to 1. Otherwise to 0. This lets
@@ -602,7 +718,7 @@ CURLcode Curl_read(struct connectdata *conn, /* connection data */
 }
 
 /* return 0 on success */
-static int showit(struct SessionHandle *data, curl_infotype type,
+static int showit(struct Curl_easy *data, curl_infotype type,
                   char *ptr, size_t size)
 {
   static const char s_infotype[CURLINFO_END][3] = {
@@ -671,7 +787,7 @@ static int showit(struct SessionHandle *data, curl_infotype type,
   return 0;
 }
 
-int Curl_debug(struct SessionHandle *data, curl_infotype type,
+int Curl_debug(struct Curl_easy *data, curl_infotype type,
                char *ptr, size_t size,
                struct connectdata *conn)
 {