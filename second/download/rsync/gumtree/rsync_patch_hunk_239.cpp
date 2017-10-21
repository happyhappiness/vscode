   }
 #endif
 
   if ((am_root && preserve_uid && st->st_uid != file->uid) || 
       (preserve_gid && st->st_gid != file->gid)) {
     updated = 1;
-    if (chown(fname,
-	      (am_root&&preserve_uid)?file->uid:-1,
-	      preserve_gid?file->gid:-1) != 0) {
+    if (lchown(fname,
+	       (am_root&&preserve_uid)?file->uid:-1,
+	       preserve_gid?file->gid:-1) != 0) {
       if (verbose>1 || preserve_uid)
 	fprintf(FERROR,"chown %s : %s\n",fname,strerror(errno));
       return updated;
     }
   }
     
