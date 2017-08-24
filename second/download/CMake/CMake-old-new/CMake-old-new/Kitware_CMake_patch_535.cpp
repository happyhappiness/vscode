@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2007, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -40,28 +40,27 @@
 #define _MPRINTF_REPLACE /* use our functions only */
 #include <curl/mprintf.h>
 
+#include "urldata.h" /* for the SessionHandle definition */
+#include "easyif.h"  /* for Curl_convert_... prototypes */
 #include "base64.h"
-#include "curl_memory.h"
+#include "memory.h"
 
 /* include memdebug.h last */
 #include "memdebug.h"
 
+/* ---- Base64 Encoding/Decoding Table --- */
+static const char table64[]=
+  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
 
 static void decodeQuantum(unsigned char *dest, const char *src)
 {
   unsigned int x = 0;
   int i;
+  char *found;
+
   for(i = 0; i < 4; i++) {
-    if(src[i] >= 'A' && src[i] <= 'Z')
-      x = (x << 6) + (unsigned int)(src[i] - 'A' + 0);
-    else if(src[i] >= 'a' && src[i] <= 'z')
-      x = (x << 6) + (unsigned int)(src[i] - 'a' + 26);
-    else if(src[i] >= '0' && src[i] <= '9')
-      x = (x << 6) + (unsigned int)(src[i] - '0' + 52);
-    else if(src[i] == '+')
-      x = (x << 6) + 62;
-    else if(src[i] == '/')
-      x = (x << 6) + 63;
+    if((found = strchr(table64, src[i])))
+      x = (x << 6) + (unsigned int)(found - table64);
     else if(src[i] == '=')
       x = (x << 6);
   }
@@ -76,43 +75,63 @@ static void decodeQuantum(unsigned char *dest, const char *src)
 /*
  * Curl_base64_decode()
  *
- * Given a base64 string at src, decode it into the memory pointed to by
- * dest. Returns the length of the decoded data.
+ * Given a base64 string at src, decode it and return an allocated memory in
+ * the *outptr. Returns the length of the decoded data.
  */
-size_t Curl_base64_decode(const char *src, char *dest)
+size_t Curl_base64_decode(const char *src, unsigned char **outptr)
 {
   int length = 0;
   int equalsTerm = 0;
   int i;
   int numQuantums;
   unsigned char lastQuantum[3];
-  size_t rawlen;
+  size_t rawlen=0;
+  unsigned char *newstr;
+
+  *outptr = NULL;
 
   while((src[length] != '=') && src[length])
     length++;
-  while(src[length+equalsTerm] == '=')
+  /* A maximum of two = padding characters is allowed */
+  if(src[length] == '=') {
     equalsTerm++;
-
+    if(src[length+equalsTerm] == '=')
+      equalsTerm++;
+  }
   numQuantums = (length + equalsTerm) / 4;
 
+  /* Don't allocate a buffer if the decoded length is 0 */
+  if (numQuantums <= 0)
+    return 0;
+
   rawlen = (numQuantums * 3) - equalsTerm;
 
+  /* The buffer must be large enough to make room for the last quantum
+  (which may be partially thrown out) and the zero terminator. */
+  newstr = malloc(rawlen+4);
+  if(!newstr)
+    return 0;
+
+  *outptr = newstr;
+
+  /* Decode all but the last quantum (which may not decode to a
+  multiple of 3 bytes) */
   for(i = 0; i < numQuantums - 1; i++) {
-    decodeQuantum((unsigned char *)dest, src);
-    dest += 3; src += 4;
+    decodeQuantum((unsigned char *)newstr, src);
+    newstr += 3; src += 4;
   }
 
+  /* This final decode may actually read slightly past the end of the buffer
+  if the input string is missing pad bytes.  This will almost always be
+  harmless. */
   decodeQuantum(lastQuantum, src);
   for(i = 0; i < 3 - equalsTerm; i++)
-    dest[i] = lastQuantum[i];
+    newstr[i] = lastQuantum[i];
 
+  newstr[i] = 0; /* zero terminate */
   return rawlen;
 }
 
-/* ---- Base64 Encoding --- */
-static char table64[]=
-  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
-
 /*
  * Curl_base64_encode()
  *
@@ -121,14 +140,18 @@ static char table64[]=
  * went wrong, -1 is returned.
  *
  */
-size_t Curl_base64_encode(const char *inp, size_t insize, char **outptr)
+size_t Curl_base64_encode(struct SessionHandle *data,
+                          const char *inp, size_t insize, char **outptr)
 {
   unsigned char ibuf[3];
   unsigned char obuf[4];
   int i;
   int inputparts;
   char *output;
   char *base64data;
+#ifdef CURL_DOES_CONVERSIONS
+  char *convbuf;
+#endif
 
   char *indata = (char *)inp;
 
@@ -141,6 +164,28 @@ size_t Curl_base64_encode(const char *inp, size_t insize, char **outptr)
   if(NULL == output)
     return 0;
 
+#ifdef CURL_DOES_CONVERSIONS
+  /*
+   * The base64 data needs to be created using the network encoding
+   * not the host encoding.  And we can't change the actual input
+   * so we copy it to a buffer, translate it, and use that instead.
+   */
+  if(data) {
+    convbuf = (char*)malloc(insize);
+    if(!convbuf) {
+      return 0;
+    }
+    memcpy(convbuf, indata, insize);
+    if(CURLE_OK != Curl_convert_to_network(data, convbuf, insize)) {
+      free(convbuf);
+      return 0;
+    }
+    indata = convbuf; /* switch to the converted buffer */
+  }
+#else
+  (void)data;
+#endif
+
   while(insize > 0) {
     for (i = inputparts = 0; i < 3; i++) {
       if(insize > 0) {
@@ -153,10 +198,12 @@ size_t Curl_base64_encode(const char *inp, size_t insize, char **outptr)
         ibuf[i] = 0;
     }
 
-    obuf [0] = (ibuf [0] & 0xFC) >> 2;
-    obuf [1] = ((ibuf [0] & 0x03) << 4) | ((ibuf [1] & 0xF0) >> 4);
-    obuf [2] = ((ibuf [1] & 0x0F) << 2) | ((ibuf [2] & 0xC0) >> 6);
-    obuf [3] = ibuf [2] & 0x3F;
+    obuf[0] = (unsigned char)  ((ibuf[0] & 0xFC) >> 2);
+    obuf[1] = (unsigned char) (((ibuf[0] & 0x03) << 4) | \
+                               ((ibuf[1] & 0xF0) >> 4));
+    obuf[2] = (unsigned char) (((ibuf[1] & 0x0F) << 2) | \
+                               ((ibuf[2] & 0xC0) >> 6));
+    obuf[3] = (unsigned char)   (ibuf[2] & 0x3F);
 
     switch(inputparts) {
     case 1: /* only one byte read */
@@ -183,6 +230,10 @@ size_t Curl_base64_encode(const char *inp, size_t insize, char **outptr)
   *output=0;
   *outptr = base64data; /* make it return the actual data memory */
 
+#ifdef CURL_DOES_CONVERSIONS
+  if(data)
+    free(convbuf);
+#endif
   return strlen(base64data); /* return the length of the new data */
 }
 /* ---- End of Base64 Encoding ---- */
@@ -205,14 +256,26 @@ int main(int argc, char **argv, char **envp)
   size_t base64Len;
   unsigned char *data;
   int dataLen;
+  struct SessionHandle *handle = NULL;
 
+#ifdef CURL_DOES_CONVERSIONS
+  /* get a Curl handle so Curl_base64_encode can translate properly */
+  handle = curl_easy_init();
+  if(handle == NULL) {
+    fprintf(stderr, "Error: curl_easy_init failed\n");
+    return 0;
+  }
+#endif
   data = (unsigned char *)suck(&dataLen);
-  base64Len = Curl_base64_encode(data, dataLen, &base64);
+  base64Len = Curl_base64_encode(handle, data, dataLen, &base64);
 
   fprintf(stderr, "%d\n", base64Len);
-  fprintf(stdout, "%s",   base64);
+  fprintf(stdout, "%s\n", base64);
 
   free(base64); free(data);
+#ifdef CURL_DOES_CONVERSIONS
+  curl_easy_cleanup(handle);
+#endif
   return 0;
 }
 #endif
@@ -235,10 +298,17 @@ int main(int argc, char **argv, char **envp)
   unsigned char *data;
   int dataLen;
   int i, j;
+#ifdef CURL_DOES_CONVERSIONS
+  /* get a Curl handle so main can translate properly */
+  struct SessionHandle *handle = curl_easy_init();
+  if(handle == NULL) {
+    fprintf(stderr, "Error: curl_easy_init failed\n");
+    return 0;
+  }
+#endif
 
   base64 = (char *)suck(&base64Len);
-  data = (unsigned char *)malloc(base64Len * 3/4 + 8);
-  dataLen = Curl_base64_decode(base64, data);
+  dataLen = Curl_base64_decode(base64, &data);
 
   fprintf(stderr, "%d\n", dataLen);
 
@@ -253,13 +323,21 @@ int main(int argc, char **argv, char **envp)
     printf(" | ");
 
     for(j=0; j < 0x10; j++)
-      if((j+i) < dataLen)
-        printf("%c", isgraph(data[i+j])?data[i+j]:'.');
-      else
+      if((j+i) < dataLen) {
+#ifdef CURL_DOES_CONVERSIONS
+        if(CURLE_OK !=
+             Curl_convert_from_network(handle, &data[i+j], (size_t)1))
+          data[i+j] = '.';
+#endif /* CURL_DOES_CONVERSIONS */
+        printf("%c", ISGRAPH(data[i+j])?data[i+j]:'.');
+      } else
         break;
     puts("");
   }
 
+#ifdef CURL_DOES_CONVERSIONS
+  curl_easy_cleanup(handle);
+#endif
   free(base64); free(data);
   return 0;
 }