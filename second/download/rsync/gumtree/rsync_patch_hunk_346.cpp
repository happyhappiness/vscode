     buf = map_file(fd,st.st_size);
   } else {
     buf = NULL;
   }
 
   if (verbose > 3)
-    fprintf(FERROR,"gen mapped %s of size %d\n",fname,(int)st.st_size);
+    fprintf(FINFO,"gen mapped %s of size %d\n",fname,(int)st.st_size);
 
-  s = generate_sums(buf,st.st_size,block_size);
+  s = generate_sums(buf,st.st_size,adapt_block_size(file, block_size));
 
   if (verbose > 2)
-    fprintf(FERROR,"sending sums for %d\n",i);
+    fprintf(FINFO,"sending sums for %d\n",i);
 
   write_int(f_out,i);
   send_sums(s,f_out);
   write_flush(f_out);
 
   close(fd);
