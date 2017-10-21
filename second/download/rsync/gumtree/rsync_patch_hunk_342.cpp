 	if (strcmp(lnk,file->link) == 0) {
 	  set_perms(fname,file,&st,1);
 	  return;
 	}
       }
     }
-    if (!dry_run) unlink(fname);
-    if (!dry_run && symlink(file->link,fname) != 0) {
+    delete_file(fname);
+    if (do_symlink(file->link,fname) != 0) {
       fprintf(FERROR,"link %s -> %s : %s\n",
 	      fname,file->link,strerror(errno));
     } else {
       set_perms(fname,file,NULL,0);
       if (verbose) 
 	fprintf(FINFO,"%s -> %s\n",
