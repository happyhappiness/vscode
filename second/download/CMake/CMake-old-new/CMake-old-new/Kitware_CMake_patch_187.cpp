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
@@ -23,13 +23,13 @@
 /* Base64 encoding/decoding */
 
 #include "curl_setup.h"
-#include "curl_printf.h"
-#include "urldata.h" /* for the SessionHandle definition */
+#include "urldata.h" /* for the Curl_easy definition */
 #include "warnless.h"
 #include "curl_base64.h"
 #include "non-ascii.h"
 
-/* The last #include files should be: */
+/* The last 3 #include files should be in this order */
+#include "curl_printf.h"
 #include "curl_memory.h"
 #include "memdebug.h"
 
@@ -169,11 +169,11 @@ CURLcode Curl_base64_decode(const char *src,
 }
 
 static CURLcode base64_encode(const char *table64,
-                              struct SessionHandle *data,
+                              struct Curl_easy *data,
                               const char *inputbuff, size_t insize,
                               char **outptr, size_t *outlen)
 {
-  CURLcode error;
+  CURLcode result;
   unsigned char ibuf[3];
   unsigned char obuf[4];
   int i;
@@ -187,22 +187,22 @@ static CURLcode base64_encode(const char *table64,
   *outptr = NULL;
   *outlen = 0;
 
-  if(0 == insize)
+  if(!insize)
     insize = strlen(indata);
 
-  base64data = output = malloc(insize*4/3+4);
-  if(NULL == output)
+  base64data = output = malloc(insize * 4 / 3 + 4);
+  if(!output)
     return CURLE_OUT_OF_MEMORY;
 
   /*
    * The base64 data needs to be created using the network encoding
    * not the host encoding.  And we can't change the actual input
    * so we copy it to a buffer, translate it, and use that instead.
    */
-  error = Curl_convert_clone(data, indata, insize, &convbuf);
-  if(error) {
+  result = Curl_convert_clone(data, indata, insize, &convbuf);
+  if(result) {
     free(output);
-    return error;
+    return result;
   }
 
   if(convbuf)
@@ -233,28 +233,35 @@ static CURLcode base64_encode(const char *table64,
                table64[obuf[0]],
                table64[obuf[1]]);
       break;
+
     case 2: /* two bytes read */
       snprintf(output, 5, "%c%c%c=",
                table64[obuf[0]],
                table64[obuf[1]],
                table64[obuf[2]]);
       break;
+
     default:
       snprintf(output, 5, "%c%c%c%c",
                table64[obuf[0]],
                table64[obuf[1]],
                table64[obuf[2]],
-               table64[obuf[3]] );
+               table64[obuf[3]]);
       break;
     }
     output += 4;
   }
+
+  /* Zero terminate */
   *output = '\0';
-  *outptr = base64data; /* return pointer to new data, allocated memory */
+
+  /* Return the pointer to the new data (allocated memory) */
+  *outptr = base64data;
 
   free(convbuf);
 
-  *outlen = strlen(base64data); /* return the length of the new data */
+  /* Return the length of the new data */
+  *outlen = strlen(base64data);
 
   return CURLE_OK;
 }
@@ -276,7 +283,7 @@ static CURLcode base64_encode(const char *table64,
  *
  * @unittest: 1302
  */
-CURLcode Curl_base64_encode(struct SessionHandle *data,
+CURLcode Curl_base64_encode(struct Curl_easy *data,
                             const char *inputbuff, size_t insize,
                             char **outptr, size_t *outlen)
 {
@@ -300,10 +307,9 @@ CURLcode Curl_base64_encode(struct SessionHandle *data,
  *
  * @unittest: 1302
  */
-CURLcode Curl_base64url_encode(struct SessionHandle *data,
+CURLcode Curl_base64url_encode(struct Curl_easy *data,
                                const char *inputbuff, size_t insize,
                                char **outptr, size_t *outlen)
 {
   return base64_encode(base64url, data, inputbuff, insize, outptr, outlen);
 }
-/* ---- End of Base64 Encoding ---- */