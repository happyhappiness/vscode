       if (do_unlink(fname) != 0) {
 	fprintf(FERROR,"unlink %s : %s\n",fname,strerror(errno));
 	return;
       }
       statret = -1;
     }
-    if (statret != 0 && mkdir(fname,file->mode) != 0 && errno != EEXIST) {
+    if (statret != 0 && do_mkdir(fname,file->mode) != 0 && errno != EEXIST) {
 	    if (!(relative_paths && errno==ENOENT && 
 		  create_directory_path(fname)==0 && 
-		  mkdir(fname,file->mode)==0)) {
+		  do_mkdir(fname,file->mode)==0)) {
 		    fprintf(FERROR,"mkdir %s : %s (2)\n",
 			    fname,strerror(errno));
 	    }
     }
     if (set_perms(fname,file,NULL,0) && verbose) 
       fprintf(FINFO,"%s/\n",fname);
