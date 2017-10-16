 }
 #endif
 
 #ifdef TEST_DECODE
 /* decoding test harness. Read in a base64 string from stdin and write out the 
  * length returned by Curl_base64_decode, followed by the decoded data itself
+ *
+ * gcc -DTEST_DECODE base64.c -o base64 mprintf.o memdebug.o
  */
 #include <stdio.h>
 
 #define TEST_NEED_SUCK
 void *suck(int *);
 
 int main(int argc, char **argv, char **envp)
 {
   char *base64;
   int base64Len;
   unsigned char *data;
   int dataLen;
+  int i, j;
 	
   base64 = (char *)suck(&base64Len);
   data = (unsigned char *)malloc(base64Len * 3/4 + 8);
   dataLen = Curl_base64_decode(base64, data);
   
   fprintf(stderr, "%d\n", dataLen);
-  fwrite(data,1,dataLen,stdout);
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
   
   free(base64); free(data);
   return 0;
 }
 #endif
 
