@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -60,7 +60,6 @@
 #include "hostip.h"
 #include "share.h"
 #include "strdup.h"
-#include "curl_memory.h"
 #include "progress.h"
 #include "easyif.h"
 #include "select.h"
@@ -74,11 +73,11 @@
 #include "conncache.h"
 #include "multiif.h"
 #include "sigpipe.h"
+#include "ssh.h"
+#include "curl_printf.h"
 
-#define _MPRINTF_REPLACE /* use our functions only */
-#include <curl/mprintf.h>
-
-/* The last #include file should be: */
+/* The last #include files should be: */
+#include "curl_memory.h"
 #include "memdebug.h"
 
 /* win32_cleanup() is for win32 socket cleanup functionality, the opposite
@@ -136,9 +135,9 @@ static CURLcode win32_init(void)
 
 #ifdef USE_WINDOWS_SSPI
   {
-    CURLcode err = Curl_sspi_global_init();
-    if(err != CURLE_OK)
-      return err;
+    CURLcode result = Curl_sspi_global_init();
+    if(result)
+      return result;
   }
 #endif
 
@@ -243,7 +242,7 @@ CURLcode curl_global_init(long flags)
     }
 
   if(flags & CURL_GLOBAL_WIN32)
-    if(win32_init() != CURLE_OK) {
+    if(win32_init()) {
       DEBUGF(fprintf(stderr, "Error: win32_init failed\n"));
       return CURLE_FAILED_INIT;
     }
@@ -265,7 +264,7 @@ CURLcode curl_global_init(long flags)
   idna_init();
 #endif
 
-  if(Curl_resolver_global_init() != CURLE_OK) {
+  if(Curl_resolver_global_init()) {
     DEBUGF(fprintf(stderr, "Error: resolver_global_init failed\n"));
     return CURLE_FAILED_INIT;
   }
@@ -293,7 +292,7 @@ CURLcode curl_global_init_mem(long flags, curl_malloc_callback m,
                               curl_free_callback f, curl_realloc_callback r,
                               curl_strdup_callback s, curl_calloc_callback c)
 {
-  CURLcode code = CURLE_OK;
+  CURLcode result = CURLE_OK;
 
   /* Invalid input, return immediately */
   if(!m || !f || !r || !s || !c)
@@ -308,16 +307,16 @@ CURLcode curl_global_init_mem(long flags, curl_malloc_callback m,
   }
 
   /* Call the actual init function first */
-  code = curl_global_init(flags);
-  if(code == CURLE_OK) {
+  result = curl_global_init(flags);
+  if(!result) {
     Curl_cmalloc = m;
     Curl_cfree = f;
     Curl_cstrdup = s;
     Curl_crealloc = r;
     Curl_ccalloc = c;
   }
 
-  return code;
+  return result;
 }
 
 /**
@@ -357,22 +356,22 @@ void curl_global_cleanup(void)
  */
 CURL *curl_easy_init(void)
 {
-  CURLcode res;
+  CURLcode result;
   struct SessionHandle *data;
 
   /* Make sure we inited the global SSL stuff */
   if(!initialized) {
-    res = curl_global_init(CURL_GLOBAL_DEFAULT);
-    if(res) {
+    result = curl_global_init(CURL_GLOBAL_DEFAULT);
+    if(result) {
       /* something in the global init failed, return nothing */
       DEBUGF(fprintf(stderr, "Error: curl_global_init failed\n"));
       return NULL;
     }
   }
 
   /* We use curl_open() with undefined URL so far */
-  res = Curl_open(&data);
-  if(res != CURLE_OK) {
+  result = Curl_open(&data);
+  if(result) {
     DEBUGF(fprintf(stderr, "Error: Curl_open failed\n"));
     return NULL;
   }
@@ -390,17 +389,17 @@ CURLcode curl_easy_setopt(CURL *curl, CURLoption tag, ...)
 {
   va_list arg;
   struct SessionHandle *data = curl;
-  CURLcode ret;
+  CURLcode result;
 
   if(!curl)
     return CURLE_BAD_FUNCTION_ARGUMENT;
 
   va_start(arg, tag);
 
-  ret = Curl_setopt(data, tag, arg);
+  result = Curl_setopt(data, tag, arg);
 
   va_end(arg);
-  return ret;
+  return result;
 }
 
 #ifdef CURLDEBUG
@@ -490,6 +489,10 @@ static int events_socket(CURL *easy,      /* easy handle */
   struct events *ev = userp;
   struct socketmonitor *m;
   struct socketmonitor *prev=NULL;
+
+#if defined(CURL_DISABLE_VERBOSE_STRINGS)
+  (void) easy;
+#endif
   (void)socketp;
 
   m = ev->list;
@@ -570,7 +573,7 @@ static CURLcode wait_or_timeout(struct Curl_multi *multi, struct events *ev)
 {
   bool done = FALSE;
   CURLMcode mcode;
-  CURLcode rc = CURLE_OK;
+  CURLcode result = CURLE_OK;
 
   while(!done) {
     CURLMsg *msg;
@@ -630,19 +633,22 @@ static CURLcode wait_or_timeout(struct Curl_multi *multi, struct events *ev)
         ev->ms += curlx_tvdiff(after, before);
 
     }
+    else
+      return CURLE_RECV_ERROR;
+
     if(mcode)
       return CURLE_URL_MALFORMAT; /* TODO: return a proper error! */
 
     /* we don't really care about the "msgs_in_queue" value returned in the
        second argument */
     msg = curl_multi_info_read(multi, &pollrc);
     if(msg) {
-      rc = msg->data.result;
+      result = msg->data.result;
       done = TRUE;
     }
   }
 
-  return rc;
+  return result;
 }
 
 
@@ -668,7 +674,7 @@ static CURLcode easy_transfer(CURLM *multi)
 {
   bool done = FALSE;
   CURLMcode mcode = CURLM_OK;
-  CURLcode code = CURLE_OK;
+  CURLcode result = CURLE_OK;
   struct timeval before;
   int without_fds = 0;  /* count number of consecutive returns from
                            curl_multi_wait() without any filedescriptors */
@@ -683,7 +689,7 @@ static CURLcode easy_transfer(CURLM *multi)
     if(mcode == CURLM_OK) {
       if(ret == -1) {
         /* poll() failed not on EINTR, indicate a network problem */
-        code = CURLE_RECV_ERROR;
+        result = CURLE_RECV_ERROR;
         break;
       }
       else if(ret == 0) {
@@ -714,7 +720,7 @@ static CURLcode easy_transfer(CURLM *multi)
       int rc;
       CURLMsg *msg = curl_multi_info_read(multi, &rc);
       if(msg) {
-        code = msg->data.result;
+        result = msg->data.result;
         done = TRUE;
       }
     }
@@ -728,7 +734,7 @@ static CURLcode easy_transfer(CURLM *multi)
             CURLE_BAD_FUNCTION_ARGUMENT;
   }
 
-  return code;
+  return result;
 }
 
 
@@ -753,7 +759,7 @@ static CURLcode easy_perform(struct SessionHandle *data, bool events)
 {
   CURLM *multi;
   CURLMcode mcode;
-  CURLcode code = CURLE_OK;
+  CURLcode result = CURLE_OK;
   SIGPIPE_VARIABLE(pipe_st);
 
   if(!data)
@@ -794,7 +800,7 @@ static CURLcode easy_perform(struct SessionHandle *data, bool events)
   data->multi = multi;
 
   /* run the transfer */
-  code = events ? easy_events(multi) : easy_transfer(multi);
+  result = events ? easy_events(multi) : easy_transfer(multi);
 
   /* ignoring the return code isn't nice, but atm we can't really handle
      a failure here, room for future improvement! */
@@ -803,7 +809,7 @@ static CURLcode easy_perform(struct SessionHandle *data, bool events)
   sigpipe_restore(&pipe_st);
 
   /* The multi handle is kept alive, owned by the easy handle */
-  return code;
+  return result;
 }
 
 
@@ -854,16 +860,16 @@ CURLcode curl_easy_getinfo(CURL *curl, CURLINFO info, ...)
 {
   va_list arg;
   void *paramp;
-  CURLcode ret;
+  CURLcode result;
   struct SessionHandle *data = (struct SessionHandle *)curl;
 
   va_start(arg, info);
   paramp = va_arg(arg, void *);
 
-  ret = Curl_getinfo(data, info, paramp);
+  result = Curl_getinfo(data, info, paramp);
 
   va_end(arg);
-  return ret;
+  return result;
 }
 
 /*
@@ -890,7 +896,7 @@ CURL *curl_easy_duphandle(CURL *incurl)
   outcurl->state.headersize = HEADERSIZE;
 
   /* copy all userdefined values */
-  if(Curl_dupset(outcurl, data) != CURLE_OK)
+  if(Curl_dupset(outcurl, data))
     goto fail;
 
   /* the connection cache is setup on demand */
@@ -936,7 +942,7 @@ CURL *curl_easy_duphandle(CURL *incurl)
 
   /* Clone the resolver handle, if present, for the new handle */
   if(Curl_resolver_duphandle(&outcurl->state.resolver,
-                             data->state.resolver) != CURLE_OK)
+                             data->state.resolver))
     goto fail;
 
   Curl_convert_setup(outcurl);
@@ -1018,73 +1024,15 @@ CURLcode curl_easy_pause(CURL *curl, int action)
     /* we have a buffer for sending that we now seem to be able to deliver
        since the receive pausing is lifted! */
 
-    /* get the pointer, type and length in local copies since the function may
-       return PAUSE again and then we'll get a new copy allocted and stored in
+    /* get the pointer in local copy since the function may return PAUSE
+       again and then we'll get a new copy allocted and stored in
        the tempwrite variables */
     char *tempwrite = data->state.tempwrite;
-    char *freewrite = tempwrite; /* store this pointer to free it later */
-    size_t tempsize = data->state.tempwritesize;
-    int temptype = data->state.tempwritetype;
-    size_t chunklen;
-
-    /* clear tempwrite here just to make sure it gets cleared if there's no
-       further use of it, and make sure we don't clear it after the function
-       invoke as it may have been set to a new value by then */
-    data->state.tempwrite = NULL;
-
-    /* since the write callback API is define to never exceed
-       CURL_MAX_WRITE_SIZE bytes in a single call, and since we may in fact
-       have more data than that in our buffer here, we must loop sending the
-       data in multiple calls until there's no data left or we get another
-       pause returned.
-
-       A tricky part is that the function we call will "buffer" the data
-       itself when it pauses on a particular buffer, so we may need to do some
-       extra trickery if we get a pause return here.
-    */
-    do {
-      chunklen = (tempsize > CURL_MAX_WRITE_SIZE)?CURL_MAX_WRITE_SIZE:tempsize;
-
-      result = Curl_client_write(data->easy_conn,
-                                 temptype, tempwrite, chunklen);
-      if(result)
-        /* failures abort the loop at once */
-        break;
-
-      if(data->state.tempwrite && (tempsize - chunklen)) {
-        /* Ouch, the reading is again paused and the block we send is now
-           "cached". If this is the final chunk we can leave it like this, but
-           if we have more chunks that are cached after this, we need to free
-           the newly cached one and put back a version that is truly the entire
-           contents that is saved for later
-        */
-        char *newptr;
-
-        /* note that tempsize is still the size as before the callback was
-           used, and thus the whole piece of data to keep */
-        newptr = realloc(data->state.tempwrite, tempsize);
-
-        if(!newptr) {
-          free(data->state.tempwrite); /* free old area */
-          data->state.tempwrite = NULL;
-          result = CURLE_OUT_OF_MEMORY;
-          /* tempwrite will be freed further down */
-          break;
-        }
-        data->state.tempwrite = newptr; /* store new pointer */
-        memcpy(newptr, tempwrite, tempsize);
-        data->state.tempwritesize = tempsize; /* store new size */
-        /* tempwrite will be freed further down */
-        break; /* go back to pausing until further notice */
-      }
-      else {
-        tempsize -= chunklen;  /* left after the call above */
-        tempwrite += chunklen; /* advance the pointer */
-      }
 
-    } while((result == CURLE_OK) && tempsize);
-
-    free(freewrite); /* this is unconditionally no longer used */
+    data->state.tempwrite = NULL;
+    result = Curl_client_chop_write(data->easy_conn, data->state.tempwritetype,
+                                    tempwrite, data->state.tempwritesize);
+    free(tempwrite);
   }
 
   /* if there's no error and we're not pausing both directions, we want
@@ -1129,20 +1077,20 @@ static CURLcode easy_connection(struct SessionHandle *data,
 CURLcode curl_easy_recv(CURL *curl, void *buffer, size_t buflen, size_t *n)
 {
   curl_socket_t sfd;
-  CURLcode ret;
+  CURLcode result;
   ssize_t n1;
   struct connectdata *c;
   struct SessionHandle *data = (struct SessionHandle *)curl;
 
-  ret = easy_connection(data, &sfd, &c);
-  if(ret)
-    return ret;
+  result = easy_connection(data, &sfd, &c);
+  if(result)
+    return result;
 
   *n = 0;
-  ret = Curl_read(c, sfd, buffer, buflen, &n1);
+  result = Curl_read(c, sfd, buffer, buflen, &n1);
 
-  if(ret != CURLE_OK)
-    return ret;
+  if(result)
+    return result;
 
   *n = (size_t)n1;
 
@@ -1157,26 +1105,26 @@ CURLcode curl_easy_send(CURL *curl, const void *buffer, size_t buflen,
                         size_t *n)
 {
   curl_socket_t sfd;
-  CURLcode ret;
+  CURLcode result;
   ssize_t n1;
   struct connectdata *c = NULL;
   struct SessionHandle *data = (struct SessionHandle *)curl;
 
-  ret = easy_connection(data, &sfd, &c);
-  if(ret)
-    return ret;
+  result = easy_connection(data, &sfd, &c);
+  if(result)
+    return result;
 
   *n = 0;
-  ret = Curl_write(c, sfd, buffer, buflen, &n1);
+  result = Curl_write(c, sfd, buffer, buflen, &n1);
 
   if(n1 == -1)
     return CURLE_SEND_ERROR;
 
   /* detect EAGAIN */
-  if((CURLE_OK == ret) && (0 == n1))
+  if(!result && !n1)
     return CURLE_AGAIN;
 
   *n = (size_t)n1;
 
-  return ret;
+  return result;
 }