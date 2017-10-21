     if (!p) out_of_memory("map_ptr");
     p_size = len;
   }
 
   if (lseek(map_fd,offset,SEEK_SET) != offset ||
       read(map_fd,p,len) != len) {
-    fprintf(stderr,"EOF in map_ptr!\n");
+    fprintf(FERROR,"EOF in map_ptr!\n");
     exit_cleanup(1);
   }
 
   p_offset = offset;
   p_len = len;
 
