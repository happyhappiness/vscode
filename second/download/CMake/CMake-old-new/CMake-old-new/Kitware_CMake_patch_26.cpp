@@ -205,7 +205,7 @@ static CURLcode auth_digest_get_qop_values(const char *options, int *value)
 {
   char *tmp;
   char *token;
-  char *tok_buf;
+  char *tok_buf = NULL;
 
   /* Initialise the output */
   *value = 0;
@@ -360,7 +360,6 @@ CURLcode Curl_auth_create_digest_md5_message(struct Curl_easy *data,
   char qop_options[64];
   int qop_values;
   char cnonce[33];
-  unsigned int entropy[4];
   char nonceCount[] = "00000001";
   char method[]     = "AUTHENTICATE";
   char qop[]        = DIGEST_QOP_VALUE_STRING_AUTH;
@@ -387,15 +386,11 @@ CURLcode Curl_auth_create_digest_md5_message(struct Curl_easy *data,
   if(!(qop_values & DIGEST_QOP_VALUE_AUTH))
     return CURLE_BAD_CONTENT_ENCODING;
 
-  /* Generate 16 bytes of random data */
-  result = Curl_rand(data, &entropy[0], 4);
+  /* Generate 32 random hex chars, 32 bytes + 1 zero termination */
+  result = Curl_rand_hex(data, (unsigned char *)cnonce, sizeof(cnonce));
   if(result)
     return result;
 
-  /* Convert the random data into a 32 byte hex string */
-  snprintf(cnonce, sizeof(cnonce), "%08x%08x%08x%08x",
-           entropy[0], entropy[1], entropy[2], entropy[3]);
-
   /* So far so good, now calculate A1 and H(A1) according to RFC 2831 */
   ctxt = Curl_MD5_init(Curl_DIGEST_MD5);
   if(!ctxt)
@@ -563,7 +558,7 @@ CURLcode Curl_auth_decode_digest_http_message(const char *chlg,
           return CURLE_OUT_OF_MEMORY;
       }
       else if(strcasecompare(value, "qop")) {
-        char *tok_buf;
+        char *tok_buf = NULL;
         /* Tokenize the list and choose auth if possible, use a temporary
            clone of the buffer since strtok_r() ruins it */
         tmp = strdup(content);
@@ -684,12 +679,10 @@ CURLcode Curl_auth_create_digest_http_message(struct Curl_easy *data,
     digest->nc = 1;
 
   if(!digest->cnonce) {
-    unsigned int rnd[4];
-    result = Curl_rand(data, &rnd[0], 4);
+    result = Curl_rand_hex(data, (unsigned char *)cnoncebuf,
+                           sizeof(cnoncebuf));
     if(result)
       return result;
-    snprintf(cnoncebuf, sizeof(cnoncebuf), "%08x%08x%08x%08x",
-             rnd[0], rnd[1], rnd[2], rnd[3]);
 
     result = Curl_base64_encode(data, cnoncebuf, strlen(cnoncebuf),
                                 &cnonce, &cnonce_sz);