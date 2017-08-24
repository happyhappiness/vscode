@@ -1,16 +1,16 @@
 /***************************************************************************
- *                                  _   _ ____  _     
- *  Project                     ___| | | |  _ \| |    
- *                             / __| | | | |_) | |    
- *                            | (__| |_| |  _ <| |___ 
+ *                                  _   _ ____  _
+ *  Project                     ___| | | |  _ \| |
+ *                             / __| | | | |_) | |
+ *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2002, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
  * are also available at http://curl.haxx.se/docs/copyright.html.
- * 
+ *
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
  * furnished to do so, under the terms of the COPYING file.
@@ -28,7 +28,7 @@
  * a base64-encoded version to stdout, and the length returned by the
  * encoding function to stderr. Compile with -DTEST_DECODE for a program that
  * will go the other way.
- * 
+ *
  * This code will break if int is smaller than 32 bits
  */
 
@@ -41,12 +41,13 @@
 #include <curl/mprintf.h>
 
 #include "base64.h"
+#include "memory.h"
 
-#ifdef MALLOCDEBUG
+/* include memdebug.h last */
 #include "memdebug.h"
-#endif
 
-static void decodeQuantum(unsigned char *dest, char *src)
+
+static void decodeQuantum(unsigned char *dest, const char *src)
 {
   unsigned int x = 0;
   int i;
@@ -55,7 +56,7 @@ static void decodeQuantum(unsigned char *dest, char *src)
       x = (x << 6) + (unsigned int)(src[i] - 'A' + 0);
     else if(src[i] >= 'a' && src[i] <= 'z')
       x = (x << 6) + (unsigned int)(src[i] - 'a' + 26);
-    else if(src[i] >= '0' && src[i] <= '9') 
+    else if(src[i] >= '0' && src[i] <= '9')
       x = (x << 6) + (unsigned int)(src[i] - '0' + 52);
     else if(src[i] == '+')
       x = (x << 6) + 62;
@@ -65,48 +66,53 @@ static void decodeQuantum(unsigned char *dest, char *src)
       x = (x << 6);
   }
 
-  dest[2] = (unsigned char)(x & 255); x >>= 8;
-  dest[1] = (unsigned char)(x & 255); x >>= 8;
-  dest[0] = (unsigned char)(x & 255); x >>= 8;
+  dest[2] = (unsigned char)(x & 255);
+  x >>= 8;
+  dest[1] = (unsigned char)(x & 255);
+  x >>= 8;
+  dest[0] = (unsigned char)(x & 255);
 }
 
-/* base64Decode
- * Given a base64 string at src, decode it into the memory pointed
- * to by dest. If rawLength points to a valid address (ie not NULL),
- * store the length of the decoded data to it.
+/*
+ * Curl_base64_decode()
+ *
+ * Given a base64 string at src, decode it into the memory pointed to by
+ * dest. Returns the length of the decoded data.
  */
-static void base64Decode(unsigned char *dest, char *src, int *rawLength)
+size_t Curl_base64_decode(const char *src, char *dest)
 {
   int length = 0;
   int equalsTerm = 0;
   int i;
   int numQuantums;
   unsigned char lastQuantum[3];
-        
+  size_t rawlen=0;
+
   while((src[length] != '=') && src[length])
     length++;
   while(src[length+equalsTerm] == '=')
     equalsTerm++;
-  
+
   numQuantums = (length + equalsTerm) / 4;
-  if(rawLength)
-    *rawLength = (numQuantums * 3) - equalsTerm;
-  
+
+  rawlen = (numQuantums * 3) - equalsTerm;
+
   for(i = 0; i < numQuantums - 1; i++) {
-    decodeQuantum(dest, src);
+    decodeQuantum((unsigned char *)dest, src);
     dest += 3; src += 4;
   }
 
   decodeQuantum(lastQuantum, src);
   for(i = 0; i < 3 - equalsTerm; i++)
     dest[i] = lastQuantum[i];
-        
+
+  return rawlen;
 }
 
 /* ---- Base64 Encoding --- */
 static char table64[]=
   "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
-  
+
 /*
  * Curl_base64_encode()
  *
@@ -115,7 +121,7 @@ static char table64[]=
  * went wrong, -1 is returned.
  *
  */
-int Curl_base64_encode(const void *inp, int insize, char **outptr)
+size_t Curl_base64_encode(const char *inp, size_t insize, char **outptr)
 {
   unsigned char ibuf[3];
   unsigned char obuf[4];
@@ -126,16 +132,18 @@ int Curl_base64_encode(const void *inp, int insize, char **outptr)
 
   char *indata = (char *)inp;
 
+  *outptr = NULL; /* set to NULL in case of failure before we reach the end */
+
   if(0 == insize)
-    insize = (int)strlen(indata);
+    insize = strlen(indata);
 
   base64data = output = (char*)malloc(insize*4/3+4);
   if(NULL == output)
-    return -1;
+    return 0;
 
   while(insize > 0) {
-    for (i = inputparts = 0; i < 3; i++) { 
-      if(*indata) {
+    for (i = inputparts = 0; i < 3; i++) {
+      if(insize > 0) {
         inputparts++;
         ibuf[i] = *indata;
         indata++;
@@ -144,51 +152,41 @@ int Curl_base64_encode(const void *inp, int insize, char **outptr)
       else
         ibuf[i] = 0;
     }
-                       
-    obuf [0] = (unsigned char)((ibuf [0] & 0xFC) >> 2);
-    obuf [1] = (unsigned char)(((ibuf [0] & 0x03) << 4) | 
-                               ((ibuf [1] & 0xF0) >> 4));
-    obuf [2] = (unsigned char)(((ibuf [1] & 0x0F) << 2) | 
-                               ((ibuf [2] & 0xC0) >> 6));
-    obuf [3] = (unsigned char)(ibuf [2] & 0x3F);
+
+    obuf [0] = (ibuf [0] & 0xFC) >> 2;
+    obuf [1] = ((ibuf [0] & 0x03) << 4) | ((ibuf [1] & 0xF0) >> 4);
+    obuf [2] = ((ibuf [1] & 0x0F) << 2) | ((ibuf [2] & 0xC0) >> 6);
+    obuf [3] = ibuf [2] & 0x3F;
 
     switch(inputparts) {
     case 1: /* only one byte read */
-      sprintf(output, "%c%c==", 
-              table64[obuf[0]],
-              table64[obuf[1]]);
+      snprintf(output, 5, "%c%c==",
+               table64[obuf[0]],
+               table64[obuf[1]]);
       break;
     case 2: /* two bytes read */
-      sprintf(output, "%c%c%c=", 
-              table64[obuf[0]],
-              table64[obuf[1]],
-              table64[obuf[2]]);
+      snprintf(output, 5, "%c%c%c=",
+               table64[obuf[0]],
+               table64[obuf[1]],
+               table64[obuf[2]]);
       break;
     default:
-      sprintf(output, "%c%c%c%c", 
-              table64[obuf[0]],
-              table64[obuf[1]],
-              table64[obuf[2]],
-              table64[obuf[3]] );
+      snprintf(output, 5, "%c%c%c%c",
+               table64[obuf[0]],
+               table64[obuf[1]],
+               table64[obuf[2]],
+               table64[obuf[3]] );
       break;
     }
     output += 4;
   }
   *output=0;
   *outptr = base64data; /* make it return the actual data memory */
 
-  return (int)strlen(base64data); /* return the length of the new data */
+  return strlen(base64data); /* return the length of the new data */
 }
 /* ---- End of Base64 Encoding ---- */
 
-int Curl_base64_decode(const char *str, void *data)
-{
-  int ret;
-
-  base64Decode((unsigned char *)data, (char *)str, &ret);
-  return ret;
-}
-
 /************* TEST HARNESS STUFF ****************/
 
 
@@ -204,24 +202,26 @@ void *suck(int *);
 int main(int argc, char **argv, char **envp)
 {
   char *base64;
-  int base64Len;
+  size_t base64Len;
   unsigned char *data;
   int dataLen;
-        
+
   data = (unsigned char *)suck(&dataLen);
   base64Len = Curl_base64_encode(data, dataLen, &base64);
 
   fprintf(stderr, "%d\n", base64Len);
   fprintf(stdout, "%s",   base64);
-  
+
   free(base64); free(data);
   return 0;
 }
 #endif
 
 #ifdef TEST_DECODE
-/* decoding test harness. Read in a base64 string from stdin and write out the 
+/* decoding test harness. Read in a base64 string from stdin and write out the
  * length returned by Curl_base64_decode, followed by the decoded data itself
+ *
+ * gcc -DTEST_DECODE base64.c -o base64 mprintf.o memdebug.o
  */
 #include <stdio.h>
 
@@ -234,14 +234,32 @@ int main(int argc, char **argv, char **envp)
   int base64Len;
   unsigned char *data;
   int dataLen;
-        
+  int i, j;
+
   base64 = (char *)suck(&base64Len);
   data = (unsigned char *)malloc(base64Len * 3/4 + 8);
   dataLen = Curl_base64_decode(base64, data);
-  
+
   fprintf(stderr, "%d\n", dataLen);
-  fwrite(data,1,dataLen,stdout);
-  
+
+  for(i=0; i < dataLen; i+=0x10) {
+    printf("0x%02x: ", i);
+    for(j=0; j < 0x10; j++)
+      if((j+i) < dataLen)
+        printf("%02x ", data[i+j]);
+      else
+        printf("   ");
+
+    printf(" | ");
+
+    for(j=0; j < 0x10; j++)
+      if((j+i) < dataLen)
+        printf("%c", isgraph(data[i+j])?data[i+j]:'.');
+      else
+        break;
+    puts("");
+  }
+
   free(base64); free(data);
   return 0;
 }
@@ -255,24 +273,16 @@ void *suck(int *lenptr)
   unsigned char *buf = NULL;
   int lastread;
   int len = 0;
-        
+
   do {
     cursize *= 2;
     buf = (unsigned char *)realloc(buf, cursize);
     memset(buf + len, 0, cursize - len);
     lastread = fread(buf + len, 1, cursize - len, stdin);
     len += lastread;
   } while(!feof(stdin));
-  
+
   lenptr[0] = len;
   return (void *)buf;
 }
 #endif
-
-/*
- * local variables:
- * eval: (load-file "../curl-mode.el")
- * end:
- * vim600: fdm=marker
- * vim: et sw=2 ts=2 sts=2 tw=78
- */