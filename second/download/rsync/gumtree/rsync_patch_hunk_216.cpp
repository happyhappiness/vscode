 
   if (verbose > 2)
     fprintf(FERROR,"recv_generator(%s,%d)\n",fname,i);
 
   statret = lstat(fname,&st);
 
+  if (S_ISDIR(file->mode)) {
+    if (dry_run) return;
+    if (statret == 0 && !S_ISDIR(st.st_mode)) {
+      if (unlink(fname) != 0) {
+	fprintf(FERROR,"unlink %s : %s\n",fname,strerror(errno));
+	return;
+      }
+      statret = -1;
+    }
+    if (statret != 0 && mkdir(fname,file->mode) != 0 && errno != EEXIST)
+      fprintf(FERROR,"mkdir %s : %s\n",fname,strerror(errno));
+    if (set_perms(fname,file,NULL,0) && verbose) 
+      fprintf(FINFO,"%s/\n",fname);
+    return;
+  }
+
 #if SUPPORT_LINKS
   if (preserve_links && S_ISLNK(file->mode)) {
     char lnk[MAXPATHLEN];
     int l;
     if (statret == 0) {
       l = readlink(fname,lnk,MAXPATHLEN-1);
