 {
   char *base64;
   int base64Len;
   unsigned char *data;
   int dataLen;
   int i, j;
-	
+
   base64 = (char *)suck(&base64Len);
   data = (unsigned char *)malloc(base64Len * 3/4 + 8);
   dataLen = Curl_base64_decode(base64, data);
-  
+
   fprintf(stderr, "%d\n", dataLen);
 
   for(i=0; i < dataLen; i+=0x10) {
     printf("0x%02x: ", i);
     for(j=0; j < 0x10; j++)
       if((j+i) < dataLen)
         printf("%02x ", data[i+j]);
       else
         printf("   ");
-    
+
     printf(" | ");
 
     for(j=0; j < 0x10; j++)
       if((j+i) < dataLen)
         printf("%c", isgraph(data[i+j])?data[i+j]:'.');
       else
         break;
     puts("");
   }
-  
+
   free(base64); free(data);
   return 0;
 }
 #endif
 
 #ifdef TEST_NEED_SUCK
