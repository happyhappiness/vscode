 
       if (make_backups) {
 	char fnamebak[MAXPATHLEN];
 	sprintf(fnamebak,"%s%s",fname,backup_suffix);
 	if (rename(fname,fnamebak) != 0 && errno != ENOENT) {
 	  fprintf(stderr,"rename %s %s : %s\n",fname,fnamebak,strerror(errno));
-	  exit(1);
+	  exit_cleanup(1);
 	}
       }
 
       /* move tmp file over real file */
       if (rename(fnametmp,fname) != 0) {
 	fprintf(stderr,"rename %s -> %s : %s\n",
