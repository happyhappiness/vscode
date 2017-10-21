     buf = map_file(fd,st.st_size);
   } else {
     buf = NULL;
   }
 
   if (verbose > 3)
-    fprintf(FERROR,"mapped %s of size %d\n",fname,(int)st.st_size);
+    fprintf(FERROR,"gen mapped %s of size %d\n",fname,(int)st.st_size);
 
   s = generate_sums(buf,st.st_size,block_size);
 
+  if (verbose > 2)
+    fprintf(FERROR,"sending sums for %d\n",i);
+
   write_int(f_out,i);
   send_sums(s,f_out);
   write_flush(f_out);
 
   close(fd);
-  unmap_file(buf,st.st_size);
+  if (buf) unmap_file(buf);
 
   free_sums(s);
 }
 
 
 
-static void receive_data(int f_in,char *buf,int fd,char *fname)
+static int receive_data(int f_in,struct map_struct *buf,int fd,char *fname)
 {
   int i,n,remainder,len,count;
   off_t offset = 0;
   off_t offset2;
+  char *data;
+  static char file_sum1[SUM_LENGTH];
+  static char file_sum2[SUM_LENGTH];
+  char *map=NULL;
 
   count = read_int(f_in);
   n = read_int(f_in);
   remainder = read_int(f_in);
 
-  for (i=read_int(f_in); i != 0; i=read_int(f_in)) {
+  sum_init();
+
+  for (i=recv_token(f_in,&data); i != 0; i=recv_token(f_in,&data)) {
     if (i > 0) {
       if (verbose > 3)
 	fprintf(FERROR,"data recv %d at %d\n",i,(int)offset);
 
-      if (read_write(f_in,fd,i) != i) {
+      sum_update(data,i);
+
+      if (write_sparse(fd,data,i) != i) {
 	fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
 	exit_cleanup(1);
       }
       offset += i;
     } else {
       i = -(i+1);
