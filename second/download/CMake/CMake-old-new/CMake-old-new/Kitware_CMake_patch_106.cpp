@@ -40,6 +40,7 @@
 #include "strcase.h"
 #include "non-ascii.h" /* included for Curl_convert_... prototypes */
 #include "curl_printf.h"
+#include "rand.h"
 
 /* The last #include files should be: */
 #include "curl_memory.h"
@@ -59,7 +60,7 @@
    what ultimately goes over the network.
 */
 #define CURL_OUTPUT_DIGEST_CONV(a, b) \
-  result = Curl_convert_to_network(a, (char *)b, strlen((const char*)b)); \
+  result = Curl_convert_to_network(a, (char *)b, strlen((const char *)b)); \
   if(result) { \
     free(b); \
     return result; \
@@ -387,10 +388,9 @@ CURLcode Curl_auth_create_digest_md5_message(struct Curl_easy *data,
     return CURLE_BAD_CONTENT_ENCODING;
 
   /* Generate 16 bytes of random data */
-  entropy[0] = Curl_rand(data);
-  entropy[1] = Curl_rand(data);
-  entropy[2] = Curl_rand(data);
-  entropy[3] = Curl_rand(data);
+  result = Curl_rand(data, &entropy[0], 4);
+  if(result)
+    return result;
 
   /* Convert the random data into a 32 byte hex string */
   snprintf(cnonce, sizeof(cnonce), "%08x%08x%08x%08x",
@@ -684,9 +684,12 @@ CURLcode Curl_auth_create_digest_http_message(struct Curl_easy *data,
     digest->nc = 1;
 
   if(!digest->cnonce) {
+    unsigned int rnd[4];
+    result = Curl_rand(data, &rnd[0], 4);
+    if(result)
+      return result;
     snprintf(cnoncebuf, sizeof(cnoncebuf), "%08x%08x%08x%08x",
-             Curl_rand(data), Curl_rand(data),
-             Curl_rand(data), Curl_rand(data));
+             rnd[0], rnd[1], rnd[2], rnd[3]);
 
     result = Curl_base64_encode(data, cnoncebuf, strlen(cnoncebuf),
                                 &cnonce, &cnonce_sz);