@@ -50,7 +50,6 @@
 #include <sys/param.h>
 #endif
 
-#include "strequal.h"
 #include "urldata.h"
 #include <curl/curl.h>
 #include "transfer.h"
@@ -144,28 +143,6 @@ static CURLcode win32_init(void)
   return CURLE_OK;
 }
 
-#ifdef USE_LIBIDN
-/*
- * Initialise use of IDNA library.
- * It falls back to ASCII if $CHARSET isn't defined. This doesn't work for
- * idna_to_ascii_lz().
- */
-static void idna_init (void)
-{
-#ifdef WIN32
-  char buf[60];
-  UINT cp = GetACP();
-
-  if(!getenv("CHARSET") && cp > 0) {
-    snprintf(buf, sizeof(buf), "CHARSET=cp%u", cp);
-    putenv(buf);
-  }
-#else
-  /* to do? */
-#endif
-}
-#endif  /* USE_LIBIDN */
-
 /* true globals -- for curl_global_init() and curl_global_cleanup() */
 static unsigned int  initialized;
 static long          init_flags;
@@ -217,7 +194,7 @@ curl_calloc_callback Curl_ccalloc;
 #endif
 
 /**
- * curl_global_init() globally initializes cURL given a bitwise set of the
+ * curl_global_init() globally initializes curl given a bitwise set of the
  * different features of what to initialize.
  */
 static CURLcode global_init(long flags, bool memoryfuncs)
@@ -262,10 +239,6 @@ static CURLcode global_init(long flags, bool memoryfuncs)
   }
 #endif
 
-#ifdef USE_LIBIDN
-  idna_init();
-#endif
-
   if(Curl_resolver_global_init()) {
     DEBUGF(fprintf(stderr, "Error: resolver_global_init failed\n"));
     return CURLE_FAILED_INIT;
@@ -292,7 +265,7 @@ static CURLcode global_init(long flags, bool memoryfuncs)
 
 
 /**
- * curl_global_init() globally initializes cURL given a bitwise set of the
+ * curl_global_init() globally initializes curl given a bitwise set of the
  * different features of what to initialize.
  */
 CURLcode curl_global_init(long flags)
@@ -301,7 +274,7 @@ CURLcode curl_global_init(long flags)
 }
 
 /*
- * curl_global_init_mem() globally initializes cURL and also registers the
+ * curl_global_init_mem() globally initializes curl and also registers the
  * user provided callback routines.
  */
 CURLcode curl_global_init_mem(long flags, curl_malloc_callback m,
@@ -333,7 +306,7 @@ CURLcode curl_global_init_mem(long flags, curl_malloc_callback m,
 }
 
 /**
- * curl_global_cleanup() globally cleanups cURL, uses the value of
+ * curl_global_cleanup() globally cleanups curl, uses the value of
  * "init_flags" to determine what needs to be cleaned up and what doesn't.
  */
 void curl_global_cleanup(void)
@@ -995,6 +968,9 @@ void curl_easy_reset(struct Curl_easy *data)
   /* zero out Progress data: */
   memset(&data->progress, 0, sizeof(struct Progress));
 
+  /* zero out PureInfo data: */
+  Curl_initinfo(data);
+
   data->progress.flags |= PGRS_HIDE;
   data->state.current_speed = -1; /* init to negative == impossible */
 }
@@ -1044,7 +1020,7 @@ CURLcode curl_easy_pause(struct Curl_easy *data, int action)
   if(!result &&
      ((newstate&(KEEP_RECV_PAUSE|KEEP_SEND_PAUSE)) !=
       (KEEP_RECV_PAUSE|KEEP_SEND_PAUSE)) )
-    Curl_expire(data, 1); /* get this handle going again */
+    Curl_expire(data, 0); /* get this handle going again */
 
   return result;
 }