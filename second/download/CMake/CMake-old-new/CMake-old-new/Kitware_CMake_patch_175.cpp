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
@@ -64,7 +64,6 @@
 #include "easyif.h"
 #include "select.h"
 #include "sendf.h" /* for failf function prototype */
-#include "curl_ntlm.h"
 #include "connect.h" /* for Curl_getconnectinfo */
 #include "slist.h"
 #include "amigaos.h"
@@ -74,12 +73,13 @@
 #include "multiif.h"
 #include "sigpipe.h"
 #include "ssh.h"
+/* The last 3 #include files should be in this order */
 #include "curl_printf.h"
-
-/* The last #include files should be: */
 #include "curl_memory.h"
 #include "memdebug.h"
 
+void Curl_version_init(void);
+
 /* win32_cleanup() is for win32 socket cleanup functionality, the opposite
    of win32_init() */
 static void win32_cleanup(void)
@@ -120,8 +120,8 @@ static CURLcode win32_init(void)
   /* wVersionRequested in wVersion. wHighVersion contains the */
   /* highest supported version. */
 
-  if(LOBYTE( wsaData.wVersion ) != LOBYTE(wVersionRequested) ||
-     HIBYTE( wsaData.wVersion ) != HIBYTE(wVersionRequested) ) {
+  if(LOBYTE(wsaData.wVersion) != LOBYTE(wVersionRequested) ||
+     HIBYTE(wsaData.wVersion) != HIBYTE(wVersionRequested) ) {
     /* Tell the user that we couldn't find a useable */
 
     /* winsock.dll. */
@@ -220,20 +220,22 @@ curl_calloc_callback Curl_ccalloc;
  * curl_global_init() globally initializes cURL given a bitwise set of the
  * different features of what to initialize.
  */
-CURLcode curl_global_init(long flags)
+static CURLcode global_init(long flags, bool memoryfuncs)
 {
   if(initialized++)
     return CURLE_OK;
 
-  /* Setup the default memory functions here (again) */
-  Curl_cmalloc = (curl_malloc_callback)malloc;
-  Curl_cfree = (curl_free_callback)free;
-  Curl_crealloc = (curl_realloc_callback)realloc;
-  Curl_cstrdup = (curl_strdup_callback)system_strdup;
-  Curl_ccalloc = (curl_calloc_callback)calloc;
+  if(memoryfuncs) {
+    /* Setup the default memory functions here (again) */
+    Curl_cmalloc = (curl_malloc_callback)malloc;
+    Curl_cfree = (curl_free_callback)free;
+    Curl_crealloc = (curl_realloc_callback)realloc;
+    Curl_cstrdup = (curl_strdup_callback)system_strdup;
+    Curl_ccalloc = (curl_calloc_callback)calloc;
 #if defined(WIN32) && defined(UNICODE)
-  Curl_cwcsdup = (curl_wcsdup_callback)_wcsdup;
+    Curl_cwcsdup = (curl_wcsdup_callback)_wcsdup;
 #endif
+  }
 
   if(flags & CURL_GLOBAL_SSL)
     if(!Curl_ssl_init()) {
@@ -269,6 +271,8 @@ CURLcode curl_global_init(long flags)
     return CURLE_FAILED_INIT;
   }
 
+  (void)Curl_ipv6works();
+
 #if defined(USE_LIBSSH2) && defined(HAVE_LIBSSH2_INIT)
   if(libssh2_init(0)) {
     DEBUGF(fprintf(stderr, "Error: libssh2_init failed\n"));
@@ -279,11 +283,23 @@ CURLcode curl_global_init(long flags)
   if(flags & CURL_GLOBAL_ACK_EINTR)
     Curl_ack_eintr = 1;
 
-  init_flags  = flags;
+  init_flags = flags;
+
+  Curl_version_init();
 
   return CURLE_OK;
 }
 
+
+/**
+ * curl_global_init() globally initializes cURL given a bitwise set of the
+ * different features of what to initialize.
+ */
+CURLcode curl_global_init(long flags)
+{
+  return global_init(flags, TRUE);
+}
+
 /*
  * curl_global_init_mem() globally initializes cURL and also registers the
  * user provided callback routines.
@@ -292,8 +308,6 @@ CURLcode curl_global_init_mem(long flags, curl_malloc_callback m,
                               curl_free_callback f, curl_realloc_callback r,
                               curl_strdup_callback s, curl_calloc_callback c)
 {
-  CURLcode result = CURLE_OK;
-
   /* Invalid input, return immediately */
   if(!m || !f || !r || !s || !c)
     return CURLE_FAILED_INIT;
@@ -306,17 +320,16 @@ CURLcode curl_global_init_mem(long flags, curl_malloc_callback m,
     return CURLE_OK;
   }
 
-  /* Call the actual init function first */
-  result = curl_global_init(flags);
-  if(!result) {
-    Curl_cmalloc = m;
-    Curl_cfree = f;
-    Curl_cstrdup = s;
-    Curl_crealloc = r;
-    Curl_ccalloc = c;
-  }
+  /* set memory functions before global_init() in case it wants memory
+     functions */
+  Curl_cmalloc = m;
+  Curl_cfree = f;
+  Curl_cstrdup = s;
+  Curl_crealloc = r;
+  Curl_ccalloc = c;
 
-  return result;
+  /* Call the actual init function, but without setting */
+  return global_init(flags, FALSE);
 }
 
 /**
@@ -354,10 +367,10 @@ void curl_global_cleanup(void)
  * curl_easy_init() is the external interface to alloc, setup and init an
  * easy handle that is returned. If anything goes wrong, NULL is returned.
  */
-CURL *curl_easy_init(void)
+struct Curl_easy *curl_easy_init(void)
 {
   CURLcode result;
-  struct SessionHandle *data;
+  struct Curl_easy *data;
 
   /* Make sure we inited the global SSL stuff */
   if(!initialized) {
@@ -385,13 +398,12 @@ CURL *curl_easy_init(void)
  */
 
 #undef curl_easy_setopt
-CURLcode curl_easy_setopt(CURL *curl, CURLoption tag, ...)
+CURLcode curl_easy_setopt(struct Curl_easy *data, CURLoption tag, ...)
 {
   va_list arg;
-  struct SessionHandle *data = curl;
   CURLcode result;
 
-  if(!curl)
+  if(!data)
     return CURLE_BAD_FUNCTION_ARGUMENT;
 
   va_start(arg, tag);
@@ -423,7 +435,7 @@ struct events {
  * updated.
  */
 
-static int events_timer(CURLM *multi,    /* multi handle */
+static int events_timer(struct Curl_multi *multi,    /* multi handle */
                         long timeout_ms, /* see above */
                         void *userp)    /* private callback pointer */
 {
@@ -478,7 +490,7 @@ static short socketcb2poll(int pollmask)
  * Callback that gets called with information about socket activity to
  * monitor.
  */
-static int events_socket(CURL *easy,      /* easy handle */
+static int events_socket(struct Curl_easy *easy,      /* easy handle */
                          curl_socket_t s, /* socket */
                          int what,        /* see above */
                          void *userp,     /* private callback
@@ -532,14 +544,18 @@ static int events_socket(CURL *easy,      /* easy handle */
     }
     else {
       m = malloc(sizeof(struct socketmonitor));
-      m->next = ev->list;
-      m->socket.fd = s;
-      m->socket.events = socketcb2poll(what);
-      m->socket.revents = 0;
-      ev->list = m;
-      infof(easy, "socket cb: socket %d ADDED as %s%s\n", s,
-            what&CURL_POLL_IN?"IN":"",
-            what&CURL_POLL_OUT?"OUT":"");
+      if(m) {
+        m->next = ev->list;
+        m->socket.fd = s;
+        m->socket.events = socketcb2poll(what);
+        m->socket.revents = 0;
+        ev->list = m;
+        infof(easy, "socket cb: socket %d ADDED as %s%s\n", s,
+              what&CURL_POLL_IN?"IN":"",
+              what&CURL_POLL_OUT?"OUT":"");
+      }
+      else
+        return CURLE_OUT_OF_MEMORY;
     }
   }
 
@@ -552,7 +568,7 @@ static int events_socket(CURL *easy,      /* easy handle */
  *
  * Do the multi handle setups that only event-based transfers need.
  */
-static void events_setup(CURLM *multi, struct events *ev)
+static void events_setup(struct Curl_multi *multi, struct events *ev)
 {
   /* timer callback */
   curl_multi_setopt(multi, CURLMOPT_TIMERFUNCTION, events_timer);
@@ -609,7 +625,7 @@ static CURLcode wait_or_timeout(struct Curl_multi *multi, struct events *ev)
     if(0 == pollrc) {
       /* timeout! */
       ev->ms = 0;
-      /* fprintf(stderr, "call curl_multi_socket_action( TIMEOUT )\n"); */
+      /* fprintf(stderr, "call curl_multi_socket_action(TIMEOUT)\n"); */
       mcode = curl_multi_socket_action(multi, CURL_SOCKET_TIMEOUT, 0,
                                        &ev->running_handles);
     }
@@ -619,7 +635,7 @@ static CURLcode wait_or_timeout(struct Curl_multi *multi, struct events *ev)
         if(fds[i].revents) {
           /* socket activity, tell libcurl */
           int act = poll2cselect(fds[i].revents); /* convert */
-          infof(multi->easyp, "call curl_multi_socket_action( socket %d )\n",
+          infof(multi->easyp, "call curl_multi_socket_action(socket %d)\n",
                 fds[i].fd);
           mcode = curl_multi_socket_action(multi, fds[i].fd, act,
                                            &ev->running_handles);
@@ -656,7 +672,7 @@ static CURLcode wait_or_timeout(struct Curl_multi *multi, struct events *ev)
  *
  * Runs a transfer in a blocking manner using the events-based API
  */
-static CURLcode easy_events(CURLM *multi)
+static CURLcode easy_events(struct Curl_multi *multi)
 {
   struct events evs= {2, FALSE, 0, NULL, 0};
 
@@ -670,7 +686,7 @@ static CURLcode easy_events(CURLM *multi)
 #define easy_events(x) CURLE_NOT_BUILT_IN
 #endif
 
-static CURLcode easy_transfer(CURLM *multi)
+static CURLcode easy_transfer(struct Curl_multi *multi)
 {
   bool done = FALSE;
   CURLMcode mcode = CURLM_OK;
@@ -681,26 +697,22 @@ static CURLcode easy_transfer(CURLM *multi)
 
   while(!done && !mcode) {
     int still_running = 0;
-    int ret;
+    int rc;
 
     before = curlx_tvnow();
-    mcode = curl_multi_wait(multi, NULL, 0, 1000, &ret);
+    mcode = curl_multi_wait(multi, NULL, 0, 1000, &rc);
 
-    if(mcode == CURLM_OK) {
-      if(ret == -1) {
-        /* poll() failed not on EINTR, indicate a network problem */
-        result = CURLE_RECV_ERROR;
-        break;
-      }
-      else if(ret == 0) {
+    if(!mcode) {
+      if(!rc) {
         struct timeval after = curlx_tvnow();
+
         /* If it returns without any filedescriptor instantly, we need to
            avoid busy-looping during periods where it has nothing particular
            to wait for */
         if(curlx_tvdiff(after, before) <= 10) {
           without_fds++;
           if(without_fds > 2) {
-            int sleep_ms = without_fds < 10 ? (1 << (without_fds-1)): 1000;
+            int sleep_ms = without_fds < 10 ? (1 << (without_fds - 1)) : 1000;
             Curl_wait_ms(sleep_ms);
           }
         }
@@ -716,8 +728,7 @@ static CURLcode easy_transfer(CURLM *multi)
     }
 
     /* only read 'still_running' if curl_multi_perform() return OK */
-    if((mcode == CURLM_OK) && !still_running) {
-      int rc;
+    if(!mcode && !still_running) {
       CURLMsg *msg = curl_multi_info_read(multi, &rc);
       if(msg) {
         result = msg->data.result;
@@ -728,10 +739,10 @@ static CURLcode easy_transfer(CURLM *multi)
 
   /* Make sure to return some kind of error if there was a multi problem */
   if(mcode) {
-    return (mcode == CURLM_OUT_OF_MEMORY) ? CURLE_OUT_OF_MEMORY :
-            /* The other multi errors should never happen, so return
-               something suitably generic */
-            CURLE_BAD_FUNCTION_ARGUMENT;
+    result = (mcode == CURLM_OUT_OF_MEMORY) ? CURLE_OUT_OF_MEMORY :
+              /* The other multi errors should never happen, so return
+                 something suitably generic */
+              CURLE_BAD_FUNCTION_ARGUMENT;
   }
 
   return result;
@@ -755,9 +766,9 @@ static CURLcode easy_transfer(CURLM *multi)
  * DEBUG: if 'events' is set TRUE, this function will use a replacement engine
  * instead of curl_multi_perform() and use curl_multi_socket_action().
  */
-static CURLcode easy_perform(struct SessionHandle *data, bool events)
+static CURLcode easy_perform(struct Curl_easy *data, bool events)
 {
-  CURLM *multi;
+  struct Curl_multi *multi;
   CURLMcode mcode;
   CURLcode result = CURLE_OK;
   SIGPIPE_VARIABLE(pipe_st);
@@ -817,19 +828,19 @@ static CURLcode easy_perform(struct SessionHandle *data, bool events)
  * curl_easy_perform() is the external interface that performs a blocking
  * transfer as previously setup.
  */
-CURLcode curl_easy_perform(CURL *easy)
+CURLcode curl_easy_perform(struct Curl_easy *data)
 {
-  return easy_perform(easy, FALSE);
+  return easy_perform(data, FALSE);
 }
 
 #ifdef CURLDEBUG
 /*
  * curl_easy_perform_ev() is the external interface that performs a blocking
  * transfer using the event-based API internally.
  */
-CURLcode curl_easy_perform_ev(CURL *easy)
+CURLcode curl_easy_perform_ev(struct Curl_easy *data)
 {
-  return easy_perform(easy, TRUE);
+  return easy_perform(data, TRUE);
 }
 
 #endif
@@ -838,9 +849,8 @@ CURLcode curl_easy_perform_ev(CURL *easy)
  * curl_easy_cleanup() is the external interface to cleaning/freeing the given
  * easy handle.
  */
-void curl_easy_cleanup(CURL *curl)
+void curl_easy_cleanup(struct Curl_easy *data)
 {
-  struct SessionHandle *data = (struct SessionHandle *)curl;
   SIGPIPE_VARIABLE(pipe_st);
 
   if(!data)
@@ -856,12 +866,11 @@ void curl_easy_cleanup(CURL *curl)
  * information from a performed transfer and similar.
  */
 #undef curl_easy_getinfo
-CURLcode curl_easy_getinfo(CURL *curl, CURLINFO info, ...)
+CURLcode curl_easy_getinfo(struct Curl_easy *data, CURLINFO info, ...)
 {
   va_list arg;
   void *paramp;
   CURLcode result;
-  struct SessionHandle *data = (struct SessionHandle *)curl;
 
   va_start(arg, info);
   paramp = va_arg(arg, void *);
@@ -877,11 +886,9 @@ CURLcode curl_easy_getinfo(CURL *curl, CURLINFO info, ...)
  * given input easy handle. The returned handle will be a new working handle
  * with all options set exactly as the input source handle.
  */
-CURL *curl_easy_duphandle(CURL *incurl)
+struct Curl_easy *curl_easy_duphandle(struct Curl_easy *data)
 {
-  struct SessionHandle *data=(struct SessionHandle *)incurl;
-
-  struct SessionHandle *outcurl = calloc(1, sizeof(struct SessionHandle));
+  struct Curl_easy *outcurl = calloc(1, sizeof(struct Curl_easy));
   if(NULL == outcurl)
     goto fail;
 
@@ -972,10 +979,8 @@ CURL *curl_easy_duphandle(CURL *incurl)
  * curl_easy_reset() is an external interface that allows an app to re-
  * initialize a session handle to the default values.
  */
-void curl_easy_reset(CURL *curl)
+void curl_easy_reset(struct Curl_easy *data)
 {
-  struct SessionHandle *data = (struct SessionHandle *)curl;
-
   Curl_safefree(data->state.pathbuffer);
 
   data->state.path = NULL;
@@ -1004,9 +1009,8 @@ void curl_easy_reset(CURL *curl)
  *
  * Action is a bitmask consisting of CURLPAUSE_* bits in curl/curl.h
  */
-CURLcode curl_easy_pause(CURL *curl, int action)
+CURLcode curl_easy_pause(struct Curl_easy *data, int action)
 {
-  struct SessionHandle *data = (struct SessionHandle *)curl;
   struct SingleRequest *k = &data->req;
   CURLcode result = CURLE_OK;
 
@@ -1046,7 +1050,7 @@ CURLcode curl_easy_pause(CURL *curl, int action)
 }
 
 
-static CURLcode easy_connection(struct SessionHandle *data,
+static CURLcode easy_connection(struct Curl_easy *data,
                                 curl_socket_t *sfd,
                                 struct connectdata **connp)
 {
@@ -1074,13 +1078,13 @@ static CURLcode easy_connection(struct SessionHandle *data,
  * curl_easy_perform() with CURLOPT_CONNECT_ONLY option.
  * Returns CURLE_OK on success, error code on error.
  */
-CURLcode curl_easy_recv(CURL *curl, void *buffer, size_t buflen, size_t *n)
+CURLcode curl_easy_recv(struct Curl_easy *data, void *buffer, size_t buflen,
+                        size_t *n)
 {
   curl_socket_t sfd;
   CURLcode result;
   ssize_t n1;
   struct connectdata *c;
-  struct SessionHandle *data = (struct SessionHandle *)curl;
 
   result = easy_connection(data, &sfd, &c);
   if(result)
@@ -1101,14 +1105,13 @@ CURLcode curl_easy_recv(CURL *curl, void *buffer, size_t buflen, size_t *n)
  * Sends data over the connected socket. Use after successful
  * curl_easy_perform() with CURLOPT_CONNECT_ONLY option.
  */
-CURLcode curl_easy_send(CURL *curl, const void *buffer, size_t buflen,
-                        size_t *n)
+CURLcode curl_easy_send(struct Curl_easy *data, const void *buffer,
+                        size_t buflen, size_t *n)
 {
   curl_socket_t sfd;
   CURLcode result;
   ssize_t n1;
   struct connectdata *c = NULL;
-  struct SessionHandle *data = (struct SessionHandle *)curl;
 
   result = easy_connection(data, &sfd, &c);
   if(result)