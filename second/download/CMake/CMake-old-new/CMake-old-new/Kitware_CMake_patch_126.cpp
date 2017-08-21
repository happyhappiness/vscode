@@ -37,7 +37,7 @@
 #include "vtls/vtls.h"
 #include "warnless.h"
 #include "strtok.h"
-#include "rawstr.h"
+#include "strcase.h"
 #include "non-ascii.h" /* included for Curl_convert_... prototypes */
 #include "curl_printf.h"
 
@@ -217,11 +217,11 @@ static CURLcode auth_digest_get_qop_values(const char *options, int *value)
 
   token = strtok_r(tmp, ",", &tok_buf);
   while(token != NULL) {
-    if(Curl_raw_equal(token, DIGEST_QOP_VALUE_STRING_AUTH))
+    if(strcasecompare(token, DIGEST_QOP_VALUE_STRING_AUTH))
       *value |= DIGEST_QOP_VALUE_AUTH;
-    else if(Curl_raw_equal(token, DIGEST_QOP_VALUE_STRING_AUTH_INT))
+    else if(strcasecompare(token, DIGEST_QOP_VALUE_STRING_AUTH_INT))
       *value |= DIGEST_QOP_VALUE_AUTH_INT;
-    else if(Curl_raw_equal(token, DIGEST_QOP_VALUE_STRING_AUTH_CONF))
+    else if(strcasecompare(token, DIGEST_QOP_VALUE_STRING_AUTH_CONF))
       *value |= DIGEST_QOP_VALUE_AUTH_CONF;
 
     token = strtok_r(NULL, ",", &tok_buf);
@@ -306,6 +306,20 @@ static CURLcode auth_decode_digest_md5_message(const char *chlg64,
 }
 
 /*
+ * Curl_auth_is_digest_supported()
+ *
+ * This is used to evaluate if DIGEST is supported.
+ *
+ * Parameters: None
+ *
+ * Returns TRUE as DIGEST as handled by libcurl.
+ */
+bool Curl_auth_is_digest_supported(void)
+{
+  return TRUE;
+}
+
+/*
  * Curl_auth_create_digest_md5_message()
  *
  * This is used to generate an already encoded DIGEST-MD5 response message
@@ -524,31 +538,31 @@ CURLcode Curl_auth_decode_digest_http_message(const char *chlg,
 
     /* Extract a value=content pair */
     if(Curl_auth_digest_get_pair(chlg, value, content, &chlg)) {
-      if(Curl_raw_equal(value, "nonce")) {
+      if(strcasecompare(value, "nonce")) {
         free(digest->nonce);
         digest->nonce = strdup(content);
         if(!digest->nonce)
           return CURLE_OUT_OF_MEMORY;
       }
-      else if(Curl_raw_equal(value, "stale")) {
-        if(Curl_raw_equal(content, "true")) {
+      else if(strcasecompare(value, "stale")) {
+        if(strcasecompare(content, "true")) {
           digest->stale = TRUE;
           digest->nc = 1; /* we make a new nonce now */
         }
       }
-      else if(Curl_raw_equal(value, "realm")) {
+      else if(strcasecompare(value, "realm")) {
         free(digest->realm);
         digest->realm = strdup(content);
         if(!digest->realm)
           return CURLE_OUT_OF_MEMORY;
       }
-      else if(Curl_raw_equal(value, "opaque")) {
+      else if(strcasecompare(value, "opaque")) {
         free(digest->opaque);
         digest->opaque = strdup(content);
         if(!digest->opaque)
           return CURLE_OUT_OF_MEMORY;
       }
-      else if(Curl_raw_equal(value, "qop")) {
+      else if(strcasecompare(value, "qop")) {
         char *tok_buf;
         /* Tokenize the list and choose auth if possible, use a temporary
            clone of the buffer since strtok_r() ruins it */
@@ -558,10 +572,10 @@ CURLcode Curl_auth_decode_digest_http_message(const char *chlg,
 
         token = strtok_r(tmp, ",", &tok_buf);
         while(token != NULL) {
-          if(Curl_raw_equal(token, DIGEST_QOP_VALUE_STRING_AUTH)) {
+          if(strcasecompare(token, DIGEST_QOP_VALUE_STRING_AUTH)) {
             foundAuth = TRUE;
           }
-          else if(Curl_raw_equal(token, DIGEST_QOP_VALUE_STRING_AUTH_INT)) {
+          else if(strcasecompare(token, DIGEST_QOP_VALUE_STRING_AUTH_INT)) {
             foundAuthInt = TRUE;
           }
           token = strtok_r(NULL, ",", &tok_buf);
@@ -583,15 +597,15 @@ CURLcode Curl_auth_decode_digest_http_message(const char *chlg,
             return CURLE_OUT_OF_MEMORY;
         }
       }
-      else if(Curl_raw_equal(value, "algorithm")) {
+      else if(strcasecompare(value, "algorithm")) {
         free(digest->algorithm);
         digest->algorithm = strdup(content);
         if(!digest->algorithm)
           return CURLE_OUT_OF_MEMORY;
 
-        if(Curl_raw_equal(content, "MD5-sess"))
+        if(strcasecompare(content, "MD5-sess"))
           digest->algo = CURLDIGESTALGO_MD5SESS;
-        else if(Curl_raw_equal(content, "MD5"))
+        else if(strcasecompare(content, "MD5"))
           digest->algo = CURLDIGESTALGO_MD5;
         else
           return CURLE_BAD_CONTENT_ENCODING;
@@ -730,7 +744,7 @@ CURLcode Curl_auth_create_digest_http_message(struct Curl_easy *data,
 
   md5this = (unsigned char *) aprintf("%s:%s", request, uripath);
 
-  if(digest->qop && Curl_raw_equal(digest->qop, "auth-int")) {
+  if(digest->qop && strcasecompare(digest->qop, "auth-int")) {
     /* We don't support auth-int for PUT or POST at the moment.
        TODO: replace md5 of empty string with entity-body for PUT/POST */
     unsigned char *md5this2 = (unsigned char *)
@@ -806,7 +820,7 @@ CURLcode Curl_auth_create_digest_http_message(struct Curl_easy *data,
                        digest->qop,
                        request_digest);
 
-    if(Curl_raw_equal(digest->qop, "auth"))
+    if(strcasecompare(digest->qop, "auth"))
       digest->nc++; /* The nc (from RFC) has to be a 8 hex digit number 0
                        padded which tells to the server how many times you are
                        using the same nonce in the qop=auth mode */