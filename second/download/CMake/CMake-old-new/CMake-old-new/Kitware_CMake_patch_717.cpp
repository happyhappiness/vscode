@@ -61,6 +61,8 @@ static void decodeQuantum(unsigned char *dest, char *src)
       x = (x << 6) + 62;
     else if(src[i] == '/')
       x = (x << 6) + 63;
+    else if(src[i] == '=')
+      x = (x << 6);
   }
 
   dest[2] = (unsigned char)(x & 255); x >>= 8;
@@ -78,23 +80,26 @@ static void base64Decode(unsigned char *dest, char *src, int *rawLength)
   int length = 0;
   int equalsTerm = 0;
   int i;
+  int numQuantums;
   unsigned char lastQuantum[3];
         
   while((src[length] != '=') && src[length])
     length++;
   while(src[length+equalsTerm] == '=')
     equalsTerm++;
   
+  numQuantums = (length + equalsTerm) / 4;
   if(rawLength)
-    *rawLength = (length * 3 / 4) - equalsTerm;
+    *rawLength = (numQuantums * 3) - equalsTerm;
   
-  for(i = 0; i < length/4 - 1; i++) {
+  for(i = 0; i < numQuantums - 1; i++) {
     decodeQuantum(dest, src);
     dest += 3; src += 4;
   }
 
   decodeQuantum(lastQuantum, src);
-  for(i = 0; i < 3 - equalsTerm; i++) dest[i] = lastQuantum[i];
+  for(i = 0; i < 3 - equalsTerm; i++)
+    dest[i] = lastQuantum[i];
         
 }
 
@@ -194,20 +199,21 @@ int Curl_base64_decode(const char *str, void *data)
 #define TEST_NEED_SUCK
 void *suck(int *);
 
-int main(int argc, char **argv, char **envp) {
-        char *base64;
-        int base64Len;
-        unsigned char *data;
-        int dataLen;
+int main(int argc, char **argv, char **envp)
+{
+  char *base64;
+  int base64Len;
+  unsigned char *data;
+  int dataLen;
         
-        data = (unsigned char *)suck(&dataLen);
-        base64Len = Curl_base64_encode(data, dataLen, &base64);
-
-        fprintf(stderr, "%d\n", base64Len);
-        fprintf(stdout, "%s",   base64);
+  data = (unsigned char *)suck(&dataLen);
+  base64Len = Curl_base64_encode(data, dataLen, &base64);
 
-        free(base64); free(data);
-        return 0;
+  fprintf(stderr, "%d\n", base64Len);
+  fprintf(stdout, "%s",   base64);
+  
+  free(base64); free(data);
+  return 0;
 }
 #endif
 
@@ -220,47 +226,47 @@ int main(int argc, char **argv, char **envp) {
 #define TEST_NEED_SUCK
 void *suck(int *);
 
-int main(int argc, char **argv, char **envp) {
-        char *base64;
-        int base64Len;
-        unsigned char *data;
-        int dataLen;
-        
-        base64 = (char *)suck(&base64Len);
-        data = (unsigned char *)malloc(base64Len * 3/4 + 8);
-        dataLen = Curl_base64_decode(base64, data);
-
-        fprintf(stderr, "%d\n", dataLen);
-        fwrite(data,1,dataLen,stdout);
+int main(int argc, char **argv, char **envp)
+{
+  char *base64;
+  int base64Len;
+  unsigned char *data;
+  int dataLen;
         
-
-        free(base64); free(data);
-        return 0;
+  base64 = (char *)suck(&base64Len);
+  data = (unsigned char *)malloc(base64Len * 3/4 + 8);
+  dataLen = Curl_base64_decode(base64, data);
+  
+  fprintf(stderr, "%d\n", dataLen);
+  fwrite(data,1,dataLen,stdout);
+  
+  free(base64); free(data);
+  return 0;
 }
 #endif
 
 #ifdef TEST_NEED_SUCK
 /* this function 'sucks' in as much as possible from stdin */
-void *suck(int *lenptr) {
-        int cursize = 8192;
-        unsigned char *buf = NULL;
-        int lastread;
-        int len = 0;
-        
-        do {
-                cursize *= 2;
-                buf = (unsigned char *)realloc(buf, cursize);
-                memset(buf + len, 0, cursize - len);
-                lastread = fread(buf + len, 1, cursize - len, stdin);
-                len += lastread;
-        } while(!feof(stdin));
+void *suck(int *lenptr)
+{
+  int cursize = 8192;
+  unsigned char *buf = NULL;
+  int lastread;
+  int len = 0;
         
-        lenptr[0] = len;
-        return (void *)buf;
+  do {
+    cursize *= 2;
+    buf = (unsigned char *)realloc(buf, cursize);
+    memset(buf + len, 0, cursize - len);
+    lastread = fread(buf + len, 1, cursize - len, stdin);
+    len += lastread;
+  } while(!feof(stdin));
+  
+  lenptr[0] = len;
+  return (void *)buf;
 }
 #endif
 
-
 /*
  * local variables:
  * eval: (load-file "../curl-mode.el")