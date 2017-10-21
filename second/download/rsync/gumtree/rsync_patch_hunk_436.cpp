   if (am_root && preserve_devices && IS_DEVICE(file->mode)) {
     if (statret != 0 || 
 	st.st_mode != file->mode ||
 	st.st_rdev != file->rdev) {	
       delete_file(fname);
       if (verbose > 2)
-	fprintf(FINFO,"mknod(%s,0%o,0x%x)\n",
+	rprintf(FINFO,"mknod(%s,0%o,0x%x)\n",
 		fname,(int)file->mode,(int)file->rdev);
       if (do_mknod(fname,file->mode,file->rdev) != 0) {
-	fprintf(FERROR,"mknod %s : %s\n",fname,strerror(errno));
+	rprintf(FERROR,"mknod %s : %s\n",fname,strerror(errno));
       } else {
 	set_perms(fname,file,NULL,0);
 	if (verbose)
-	  fprintf(FINFO,"%s\n",fname);
+	  rprintf(FINFO,"%s\n",fname);
       }
     } else {
       set_perms(fname,file,&st,1);
     }
     return;
   }
 #endif
 
   if (preserve_hard_links && check_hard_link(file)) {
     if (verbose > 1)
-      fprintf(FINFO,"%s is a hard link\n",f_name(file));
+      rprintf(FINFO,"%s is a hard link\n",f_name(file));
     return;
   }
 
   if (!S_ISREG(file->mode)) {
-    fprintf(FINFO,"skipping non-regular file %s\n",fname);
+    rprintf(FINFO,"skipping non-regular file %s\n",fname);
     return;
   }
 
   if (statret == -1) {
     if (errno == ENOENT) {
       write_int(f_out,i);
       if (!dry_run) send_sums(NULL,f_out);
     } else {
       if (verbose > 1)
-	fprintf(FERROR,"recv_generator failed to open %s\n",fname);
+	rprintf(FERROR,"recv_generator failed to open %s\n",fname);
     }
     return;
   }
 
   if (!S_ISREG(st.st_mode)) {
     if (delete_file(fname) != 0) {
