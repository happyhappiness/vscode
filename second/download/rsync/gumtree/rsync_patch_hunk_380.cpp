 	char fnamebak[MAXPATHLEN];
 	if (strlen(fname) + strlen(backup_suffix) > (MAXPATHLEN-1)) {
 		fprintf(FERROR,"backup filename too long\n");
 		continue;
 	}
 	sprintf(fnamebak,"%s%s",fname,backup_suffix);
-	if (rename(fname,fnamebak) != 0 && errno != ENOENT) {
+	if (do_rename(fname,fnamebak) != 0 && errno != ENOENT) {
 	  fprintf(FERROR,"rename %s %s : %s\n",fname,fnamebak,strerror(errno));
 	  continue;
 	}
       }
 
       /* move tmp file over real file */
-      if (rename(fnametmp,fname) != 0) {
+      if (do_rename(fnametmp,fname) != 0) {
 	      if (errno == EXDEV) {
 		      /* rename failed on cross-filesystem link.  
 			 Copy the file instead. */
 		      if (copy_file(fnametmp,fname, file->mode)) {
 			      fprintf(FERROR,"copy %s -> %s : %s\n",
 				      fnametmp,fname,strerror(errno));
