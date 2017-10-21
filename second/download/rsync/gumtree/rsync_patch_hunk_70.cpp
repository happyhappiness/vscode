       fprintf(stderr,"stat %s : %s\n",fname,strerror(errno));
       return;
     }
     st = &st2;
   }
 
-#ifdef HAVE_UTIME
   if (preserve_times && st->st_mtime != file->modtime) {
-    struct utimbuf tbuf;  
     updated = 1;
-    tbuf.actime = time(NULL);
-    tbuf.modtime = file->modtime;
-    if (utime(fname,&tbuf) != 0) {
+    if (set_modtime(fname,file->modtime) != 0) {
       fprintf(stderr,"failed to set times on %s : %s\n",
 	      fname,strerror(errno));
       return;
     }
   }
-#endif
 
 #ifdef HAVE_CHMOD
   if (preserve_perms && st->st_mode != file->mode) {
     updated = 1;
     if (chmod(fname,file->mode) != 0) {
       fprintf(stderr,"failed to set permissions on %s : %s\n",
