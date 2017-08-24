@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2007, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -22,7 +22,7 @@
  ***************************************************************************/
 #include "setup.h"
 
-#ifndef CURL_DISABLE_HTTP
+#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_CRYPTO_AUTH)
 /* -- WIN32 approved -- */
 #include <stdio.h>
 #include <string.h>
@@ -38,7 +38,8 @@
 #include "http_digest.h"
 #include "strtok.h"
 #include "url.h" /* for Curl_safefree() */
-#include "curl_memory.h"
+#include "memory.h"
+#include "easyif.h" /* included for Curl_convert_... prototypes */
 
 #define _MPRINTF_REPLACE /* use our functions only */
 #include <curl/mprintf.h>
@@ -59,8 +60,8 @@ CURLdigest Curl_input_digest(struct connectdata *conn,
                                               header */
 {
   bool more = TRUE;
-  char *token;
-  char *tmp;
+  char *token = NULL;
+  char *tmp = NULL;
   bool foundAuth = FALSE;
   bool foundAuthInt = FALSE;
   struct SessionHandle *data=conn->data;
@@ -75,7 +76,7 @@ CURLdigest Curl_input_digest(struct connectdata *conn,
   }
 
   /* skip initial whitespaces */
-  while(*header && isspace((int)*header))
+  while(*header && ISSPACE(*header))
     header++;
 
   if(checkprefix("Digest", header)) {
@@ -91,9 +92,9 @@ CURLdigest Curl_input_digest(struct connectdata *conn,
     while(more) {
       char value[32];
       char content[128];
-      size_t totlen;
+      size_t totlen=0;
 
-      while(*header && isspace((int)*header))
+      while(*header && ISSPACE(*header))
         header++;
 
       /* how big can these strings be? */
@@ -224,7 +225,7 @@ CURLcode Curl_output_digest(struct connectdata *conn,
   unsigned char ha2[33];/* 32 digits and 1 zero byte */
   char cnoncebuf[7];
   char *cnonce;
-  char *tmp;
+  char *tmp = NULL;
   struct timeval now;
 
   char **allocuserpwd;
@@ -234,6 +235,21 @@ CURLcode Curl_output_digest(struct connectdata *conn,
 
   struct SessionHandle *data = conn->data;
   struct digestdata *d;
+#ifdef CURL_DOES_CONVERSIONS
+  CURLcode rc;
+/* The CURL_OUTPUT_DIGEST_CONV macro below is for non-ASCII machines.
+   It converts digest text to ASCII so the MD5 will be correct for 
+   what ultimately goes over the network.
+*/
+#define CURL_OUTPUT_DIGEST_CONV(a, b) \
+  rc = Curl_convert_to_network(a, (char *)b, strlen((const char*)b)); \
+  if (rc != CURLE_OK) { \
+    free(b); \
+    return rc; \
+  }
+#else
+#define CURL_OUTPUT_DIGEST_CONV(a, b)
+#endif /* CURL_DOES_CONVERSIONS */
 
   if(proxy) {
     d = &data->state.proxydigest;
@@ -270,7 +286,7 @@ CURLcode Curl_output_digest(struct connectdata *conn,
     /* Generate a cnonce */
     now = Curl_tvnow();
     snprintf(cnoncebuf, sizeof(cnoncebuf), "%06ld", now.tv_sec);
-    if(Curl_base64_encode(cnoncebuf, strlen(cnoncebuf), &cnonce))
+    if(Curl_base64_encode(data, cnoncebuf, strlen(cnoncebuf), &cnonce))
       d->cnonce = cnonce;
     else
       return CURLE_OUT_OF_MEMORY;
@@ -291,6 +307,8 @@ CURLcode Curl_output_digest(struct connectdata *conn,
     aprintf("%s:%s:%s", userp, d->realm, passwdp);
   if(!md5this)
     return CURLE_OUT_OF_MEMORY;
+
+  CURL_OUTPUT_DIGEST_CONV(data, md5this); /* convert on non-ASCII machines */
   Curl_md5it(md5buf, md5this);
   free(md5this); /* free this again */
 
@@ -303,10 +321,12 @@ CURLcode Curl_output_digest(struct connectdata *conn,
   if(d->algo == CURLDIGESTALGO_MD5SESS) {
     /* nonce and cnonce are OUTSIDE the hash */
     tmp = aprintf("%s:%s:%s", ha1, d->nonce, d->cnonce);
-    free(ha1);
     if(!tmp)
       return CURLE_OUT_OF_MEMORY;
-    ha1 = (unsigned char *)tmp;
+    CURL_OUTPUT_DIGEST_CONV(data, tmp); /* convert on non-ASCII machines */
+    Curl_md5it(md5buf, (unsigned char *)tmp);
+    free(tmp); /* free this again */
+    md5_to_ascii(md5buf, ha1);
   }
 
   /*
@@ -333,6 +353,7 @@ CURLcode Curl_output_digest(struct connectdata *conn,
        entity-body here */
     /* TODO: Append H(entity-body)*/
   }
+  CURL_OUTPUT_DIGEST_CONV(data, md5this); /* convert on non-ASCII machines */
   Curl_md5it(md5buf, md5this);
   free(md5this); /* free this again */
   md5_to_ascii(md5buf, ha2);
@@ -356,6 +377,7 @@ CURLcode Curl_output_digest(struct connectdata *conn,
   if(!md5this)
     return CURLE_OUT_OF_MEMORY;
 
+  CURL_OUTPUT_DIGEST_CONV(data, md5this); /* convert on non-ASCII machines */
   Curl_md5it(md5buf, md5this);
   free(md5this); /* free this again */
   md5_to_ascii(md5buf, request_digest);