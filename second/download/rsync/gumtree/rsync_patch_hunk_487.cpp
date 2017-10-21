     len1 = len;
     if (!buf1) out_of_memory("get_checksum2");
   }
 
   MDbegin(&MD);
 
-  bcopy(buf,buf1,len);
+  memcpy(buf1,buf,len);
   if (checksum_seed) {
     SIVAL(buf1,len,checksum_seed);
     len += 4;
   }
 
   for(i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
