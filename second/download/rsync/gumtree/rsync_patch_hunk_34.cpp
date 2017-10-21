 	st.st_mode != flist->files[i].mode ||
 	st.st_rdev != flist->files[i].dev) {	
       if (!dry_run) unlink(fname);
       if (verbose > 2)
 	fprintf(stderr,"mknod(%s,0%o,0x%x)\n",
 		fname,(int)flist->files[i].mode,(int)flist->files[i].dev);
-      if (!dry_run && mknod(fname,flist->files[i].mode,flist->files[i].dev) != 0) {
+      if (!dry_run && 
+	  mknod(fname,flist->files[i].mode,flist->files[i].dev) != 0) {
 	fprintf(stderr,"mknod %s : %s\n",fname,strerror(errno));
       } else {
+	set_perms(fname,&flist->files[i],NULL,0);
 	if (verbose)
 	  fprintf(am_server?stderr:stdout,"%s\n",fname);
-	set_perms(fname,&flist->files[i]);
       }
+    } else {
+      set_perms(fname,&flist->files[i],&st,1);
     }
     return;
   }
 #endif
 
   if (!S_ISREG(flist->files[i].mode)) {
