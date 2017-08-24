@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2006, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -31,24 +31,43 @@
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
-#include "curl_memory.h"
+#include "memory.h"
+/* urldata.h and easyif.h are included for Curl_convert_... prototypes */
+#include "urldata.h"
+#include "easyif.h"
 
 #define _MPRINTF_REPLACE /* use our functions only */
 #include <curl/mprintf.h>
 
 /* The last #include file should be: */
 #include "memdebug.h"
 
+/* for ABI-compatibility with previous versions */
 char *curl_escape(const char *string, int inlength)
 {
+  return curl_easy_escape(NULL, string, inlength);
+}
+
+/* for ABI-compatibility with previous versions */
+char *curl_unescape(const char *string, int length)
+{
+  return curl_easy_unescape(NULL, string, length, NULL);
+}
+
+char *curl_easy_escape(CURL *handle, const char *string, int inlength)
+{
   size_t alloc = (inlength?(size_t)inlength:strlen(string))+1;
   char *ns;
-  char *testing_ptr;
+  char *testing_ptr = NULL;
   unsigned char in;
   size_t newlen = alloc;
   int strindex=0;
   size_t length;
 
+#ifndef CURL_DOES_CONVERSIONS
+  /* avoid compiler warnings */
+  (void)handle;
+#endif
   ns = malloc(alloc);
   if(!ns)
     return NULL;
@@ -72,6 +91,17 @@ char *curl_escape(const char *string, int inlength)
           ns = testing_ptr;
         }
       }
+
+#ifdef CURL_DOES_CONVERSIONS
+/* escape sequences are always in ASCII so convert them on non-ASCII hosts */
+      if (!handle ||
+          (Curl_convert_to_network(handle, &in, 1) != CURLE_OK)) {
+        /* Curl_convert_to_network calls failf if unsuccessful */
+        free(ns);
+        return NULL;
+      }
+#endif /* CURL_DOES_CONVERSIONS */
+
       snprintf(&ns[strindex], 4, "%%%02X", in);
 
       strindex+=3;
@@ -86,24 +116,25 @@ char *curl_escape(const char *string, int inlength)
   return ns;
 }
 
-#define ishex(in) ((in >= 'a' && in <= 'f') || \
-                   (in >= 'A' && in <= 'F') || \
-                   (in >= '0' && in <= '9'))
-
-char *curl_unescape(const char *string, int length)
+char *curl_easy_unescape(CURL *handle, const char *string, int length,
+                         int *olen)
 {
   int alloc = (length?length:(int)strlen(string))+1;
   char *ns = malloc(alloc);
   unsigned char in;
   int strindex=0;
   long hex;
 
+#ifndef CURL_DOES_CONVERSIONS
+  /* avoid compiler warnings */
+  (void)handle;
+#endif
   if( !ns )
     return NULL;
 
   while(--alloc > 0) {
     in = *string;
-    if(('%' == in) && ishex(string[1]) && ishex(string[2])) {
+    if(('%' == in) && ISXDIGIT(string[1]) && ISXDIGIT(string[2])) {
       /* this is two hexadecimal digits following a '%' */
       char hexstr[3];
       char *ptr;
@@ -114,6 +145,17 @@ char *curl_unescape(const char *string, int length)
       hex = strtol(hexstr, &ptr, 16);
 
       in = (unsigned char)hex; /* this long is never bigger than 255 anyway */
+
+#ifdef CURL_DOES_CONVERSIONS
+/* escape sequences are always in ASCII so convert them on non-ASCII hosts */
+      if (!handle ||
+          (Curl_convert_from_network(handle, &in, 1) != CURLE_OK)) {
+        /* Curl_convert_from_network calls failf if unsuccessful */
+        free(ns);
+        return NULL;
+      }
+#endif /* CURL_DOES_CONVERSIONS */
+
       string+=2;
       alloc-=2;
     }
@@ -122,6 +164,10 @@ char *curl_unescape(const char *string, int length)
     string++;
   }
   ns[strindex]=0; /* terminate it */
+
+  if(olen)
+    /* store output size */
+    *olen = strindex;
   return ns;
 }
 