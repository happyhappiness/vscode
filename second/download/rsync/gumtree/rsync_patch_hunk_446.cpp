       if (fd1 != -1) {
 	close(fd1);
       }
       close(fd2);
 
       if (verbose > 2)
-	fprintf(FINFO,"renaming %s to %s\n",fnametmp,fname);
+	rprintf(FINFO,"renaming %s to %s\n",fnametmp,fname);
 
       if (make_backups) {
 	char fnamebak[MAXPATHLEN];
 	if (strlen(fname) + strlen(backup_suffix) > (MAXPATHLEN-1)) {
-		fprintf(FERROR,"backup filename too long\n");
+		rprintf(FERROR,"backup filename too long\n");
 		continue;
 	}
 	sprintf(fnamebak,"%s%s",fname,backup_suffix);
 	if (do_rename(fname,fnamebak) != 0 && errno != ENOENT) {
-	  fprintf(FERROR,"rename %s %s : %s\n",fname,fnamebak,strerror(errno));
+	  rprintf(FERROR,"rename %s %s : %s\n",fname,fnamebak,strerror(errno));
 	  continue;
 	}
       }
 
       /* move tmp file over real file */
       if (do_rename(fnametmp,fname) != 0) {
 	      if (errno == EXDEV) {
 		      /* rename failed on cross-filesystem link.  
 			 Copy the file instead. */
 		      if (copy_file(fnametmp,fname, file->mode)) {
-			      fprintf(FERROR,"copy %s -> %s : %s\n",
+			      rprintf(FERROR,"copy %s -> %s : %s\n",
 				      fnametmp,fname,strerror(errno));
 		      } else {
 			      set_perms(fname,file,NULL,0);
 		      }
 		      do_unlink(fnametmp);
 	      } else {
-		      fprintf(FERROR,"rename %s -> %s : %s\n",
+		      rprintf(FERROR,"rename %s -> %s : %s\n",
 			      fnametmp,fname,strerror(errno));
 		      do_unlink(fnametmp);
 	      }
       } else {
 	      set_perms(fname,file,NULL,0);
       }
 
       cleanup_fname = NULL;
 
 
       if (!recv_ok) {
 	      if (csum_length == SUM_LENGTH) {
-		      fprintf(FERROR,"ERROR: file corruption in %s. File changed during transfer?\n",
+		      rprintf(FERROR,"ERROR: file corruption in %s. File changed during transfer?\n",
 			      fname);
 	      } else {
 		      if (verbose > 1)
-			      fprintf(FINFO,"redoing %s(%d)\n",fname,i);
+			      rprintf(FINFO,"redoing %s(%d)\n",fname,i);
 		      write_int(f_gen,i);
 	      }
       }
     }
 
   if (preserve_hard_links)
