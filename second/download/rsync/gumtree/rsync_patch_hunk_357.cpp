 		      if (copy_file(fnametmp,fname, file->mode)) {
 			      fprintf(FERROR,"copy %s -> %s : %s\n",
 				      fnametmp,fname,strerror(errno));
 		      } else {
 			      set_perms(fname,file,NULL,0);
 		      }
-		      unlink(fnametmp);
+		      do_unlink(fnametmp);
 	      } else {
 		      fprintf(FERROR,"rename %s -> %s : %s\n",
 			      fnametmp,fname,strerror(errno));
-		      unlink(fnametmp);
+		      do_unlink(fnametmp);
 	      }
       } else {
 	      set_perms(fname,file,NULL,0);
       }
 
       cleanup_fname = NULL;
 
 
       if (!recv_ok) {
-	if (verbose > 1)
-	  fprintf(FERROR,"redoing %s(%d)\n",fname,i);
-        if (csum_length == SUM_LENGTH)
-	  fprintf(FERROR,"ERROR: file corruption in %s\n",fname);
-	write_int(f_gen,i);
+	      if (csum_length == SUM_LENGTH) {
+		      fprintf(FERROR,"ERROR: file corruption in %s. File changed during transfer?\n",
+			      fname);
+	      } else {
+		      if (verbose > 1)
+			      fprintf(FINFO,"redoing %s(%d)\n",fname,i);
+		      write_int(f_gen,i);
+	      }
       }
     }
 
   if (preserve_hard_links)
 	  do_hard_links(flist);
 
   /* now we need to fix any directory permissions that were 
      modified during the transfer */
   for (i = 0; i < flist->count; i++) {
-	  struct file_struct *file = &flist->files[i];
-	  if (!file->name || !S_ISDIR(file->mode)) continue;
-	  recv_generator(file->name,flist,i,-1);
+	  struct file_struct *file = flist->files[i];
+	  if (!file->basename || !S_ISDIR(file->mode)) continue;
+	  recv_generator(f_name(file),flist,i,-1);
   }
 
   if (verbose > 2)
-    fprintf(FERROR,"recv_files finished\n");
+    fprintf(FINFO,"recv_files finished\n");
   
   return 0;
 }
 
 
 
-off_t send_files(struct file_list *flist,int f_out,int f_in)
+void send_files(struct file_list *flist,int f_out,int f_in)
 { 
   int fd;
   struct sum_struct *s;
   struct map_struct *buf;
   struct stat st;
   char fname[MAXPATHLEN];  
-  off_t total=0;
   int i;
   struct file_struct *file;
   int phase = 0;
+  int offset=0;
 
   if (verbose > 2)
-    fprintf(FERROR,"send_files starting\n");
+    fprintf(FINFO,"send_files starting\n");
 
   setup_nonblocking(f_in,f_out);
 
-  while (1) 
-    {
-      i = read_int(f_in);
-      if (i == -1) {
-	if (phase==0 && remote_version >= 13) {
-	  phase++;
-	  csum_length = SUM_LENGTH;
-	  write_int(f_out,-1);
-	  write_flush(f_out);
-	  if (verbose > 2)
-	    fprintf(FERROR,"send_files phase=%d\n",phase);
-	  continue;
-	}
-	break;
-      }
-
-      file = &flist->files[i];
-
-      fname[0] = 0;
-      if (file->dir) {
-	strncpy(fname,file->dir,MAXPATHLEN-1);
-	fname[MAXPATHLEN-1] = 0;
-      if (strlen(fname) == MAXPATHLEN-1) {
-        fprintf(FERROR, "send_files failed on long-named directory %s\n",
-                fname);
-        return -1;
-      }
-	strcat(fname,"/");
-      }
-      strncat(fname,file->name,MAXPATHLEN-strlen(fname));
-
-      if (verbose > 2) 
-	fprintf(FERROR,"send_files(%d,%s)\n",i,fname);
-
-      if (dry_run) {	
-	if (!am_server && verbose)
-	  printf("%s\n",fname);
-	write_int(f_out,i);
-	continue;
-      }
-
-      s = receive_sums(f_in);
-      if (!s) {
-	fprintf(FERROR,"receive_sums failed\n");
-	return -1;
-      }
-
-      fd = open(fname,O_RDONLY);
-      if (fd == -1) {
-	fprintf(FERROR,"send_files failed to open %s: %s\n",
-		fname,strerror(errno));
-	continue;
-      }
-  
-      /* map the local file */
-      if (fstat(fd,&st) != 0) {
-	fprintf(FERROR,"fstat failed : %s\n",strerror(errno));
-	close(fd);
-	return -1;
-      }
-      
-      if (st.st_size > 0) {
-	buf = map_file(fd,st.st_size);
-      } else {
-	buf = NULL;
-      }
-
-      if (verbose > 2)
-	fprintf(FERROR,"send_files mapped %s of size %d\n",
-		fname,(int)st.st_size);
-
-      write_int(f_out,i);
-
-      write_int(f_out,s->count);
-      write_int(f_out,s->n);
-      write_int(f_out,s->remainder);
-
-      if (verbose > 2)
-	fprintf(FERROR,"calling match_sums %s\n",fname);
-
-      if (!am_server && verbose)
-	printf("%s\n",fname);
-      
-      match_sums(f_out,s,buf,st.st_size);
-      write_flush(f_out);
-      
-      if (buf) unmap_file(buf);
-      close(fd);
+  while (1) {
+	  i = read_int(f_in);
+	  if (i == -1) {
+		  if (phase==0 && remote_version >= 13) {
+			  phase++;
+			  csum_length = SUM_LENGTH;
+			  write_int(f_out,-1);
+			  write_flush(f_out);
+			  if (verbose > 2)
+				  fprintf(FINFO,"send_files phase=%d\n",phase);
+			  continue;
+		  }
+		  break;
+	  }
 
-      free_sums(s);
+	  file = flist->files[i];
 
-      if (verbose > 2)
-	fprintf(FERROR,"sender finished %s\n",fname);
+	  fname[0] = 0;
+	  if (file->basedir) {
+		  strncpy(fname,file->basedir,MAXPATHLEN-1);
+		  fname[MAXPATHLEN-1] = 0;
+		  if (strlen(fname) == MAXPATHLEN-1) {
+			  io_error = 1;
+			  fprintf(FERROR, "send_files failed on long-named directory %s\n",
+				  fname);
+			  return;
+		  }
+		  strcat(fname,"/");
+		  offset = strlen(file->basedir)+1;
+	  }
+	  strncat(fname,f_name(file),MAXPATHLEN-strlen(fname));
+	  
+	  if (verbose > 2) 
+		  fprintf(FINFO,"send_files(%d,%s)\n",i,fname);
+	  
+	  if (dry_run) {	
+		  if (!am_server && verbose)
+			  printf("%s\n",fname);
+		  write_int(f_out,i);
+		  continue;
+	  }
 
-      total += st.st_size;
-    }
+	  s = receive_sums(f_in);
+	  if (!s) {
+		  io_error = 1;
+		  fprintf(FERROR,"receive_sums failed\n");
+		  return;
+	  }
+	  
+	  fd = open(fname,O_RDONLY);
+	  if (fd == -1) {
+		  io_error = 1;
+		  fprintf(FERROR,"send_files failed to open %s: %s\n",
+			  fname,strerror(errno));
+		  free_sums(s);
+		  continue;
+	  }
+	  
+	  /* map the local file */
+	  if (fstat(fd,&st) != 0) {
+		  io_error = 1;
+		  fprintf(FERROR,"fstat failed : %s\n",strerror(errno));
+		  free_sums(s);
+		  close(fd);
+		  return;
+	  }
+	  
+	  if (st.st_size > 0) {
+		  buf = map_file(fd,st.st_size);
+	  } else {
+		  buf = NULL;
+	  }
+	  
+	  if (verbose > 2)
+		  fprintf(FINFO,"send_files mapped %s of size %d\n",
+			  fname,(int)st.st_size);
+	  
+	  write_int(f_out,i);
+	  
+	  write_int(f_out,s->count);
+	  write_int(f_out,s->n);
+	  write_int(f_out,s->remainder);
+	  
+	  if (verbose > 2)
+		  fprintf(FINFO,"calling match_sums %s\n",fname);
+	  
+	  if (!am_server && verbose)
+		  printf("%s\n",fname+offset);
+	  
+	  match_sums(f_out,s,buf,st.st_size);
+	  write_flush(f_out);
+	  
+	  if (buf) unmap_file(buf);
+	  close(fd);
+	  
+	  free_sums(s);
+	  
+	  if (verbose > 2)
+		  fprintf(FINFO,"sender finished %s\n",fname);
+  }
 
   if (verbose > 2)
-    fprintf(FERROR,"send files finished\n");
+	  fprintf(FINFO,"send files finished\n");
 
   match_report();
 
   write_int(f_out,-1);
   write_flush(f_out);
-
-  return total;
 }
 
 
 
 void generate_files(int f,struct file_list *flist,char *local_name,int f_recv)
 {
   int i;
   int phase=0;
 
   if (verbose > 2)
-    fprintf(FERROR,"generator starting pid=%d count=%d\n",
+    fprintf(FINFO,"generator starting pid=%d count=%d\n",
 	    (int)getpid(),flist->count);
 
   for (i = 0; i < flist->count; i++) {
-    struct file_struct *file = &flist->files[i];
+    struct file_struct *file = flist->files[i];
     mode_t saved_mode = file->mode;
-    if (!file->name) continue;
+    if (!file->basename) continue;
 
     /* we need to ensure that any directories we create have writeable
        permissions initially so that we can create the files within
        them. This is then fixed after the files are transferred */
     if (!am_root && S_ISDIR(file->mode)) {
       file->mode |= S_IWUSR; /* user write */
     }
 
-    recv_generator(local_name?local_name:file->name,
+    recv_generator(local_name?local_name:f_name(file),
 		   flist,i,f);
 
     file->mode = saved_mode;
   }
 
   phase++;
   csum_length = SUM_LENGTH;
   ignore_times=1;
 
   if (verbose > 2)
-    fprintf(FERROR,"generate_files phase=%d\n",phase);
+    fprintf(FINFO,"generate_files phase=%d\n",phase);
 
   write_int(f,-1);
   write_flush(f);
 
+  /* we expect to just sit around now, so don't exit on a timeout. If we
+     really get a timeout then the other process should exit */
+  io_timeout = 0;
+
   if (remote_version >= 13) {
     /* in newer versions of the protocol the files can cycle through
        the system more than once to catch initial checksum errors */
     for (i=read_int(f_recv); i != -1; i=read_int(f_recv)) {
-      struct file_struct *file = &flist->files[i];
-      recv_generator(local_name?local_name:file->name,
+      struct file_struct *file = flist->files[i];
+      recv_generator(local_name?local_name:f_name(file),
 		     flist,i,f);    
     }
 
     phase++;
     if (verbose > 2)
-      fprintf(FERROR,"generate_files phase=%d\n",phase);
+      fprintf(FINFO,"generate_files phase=%d\n",phase);
 
     write_int(f,-1);
     write_flush(f);
   }
 
 
   if (verbose > 2)
-    fprintf(FERROR,"generator wrote %d\n",write_total());
+    fprintf(FINFO,"generator wrote %ld\n",(long)write_total());
 }
 
 
