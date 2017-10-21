      if (fd1 != -1) {
	close(fd1);
      }
      close(fd2);

      if (verbose > 2)
	rprintf(FINFO,"renaming %s to %s\n",fnametmp,fname);

      if (make_backups) {
	char fnamebak[MAXPATHLEN];
	if (strlen(fname) + strlen(backup_suffix) > (MAXPATHLEN-1)) {
		rprintf(FERROR,"backup filename too long\n");
		continue;
	}
	sprintf(fnamebak,"%s%s",fname,backup_suffix);
	if (do_rename(fname,fnamebak) != 0 && errno != ENOENT) {
	  rprintf(FERROR,"rename %s %s : %s\n",fname,fnamebak,strerror(errno));
	  continue;
	}
      }

      /* move tmp file over real file */
      if (do_rename(fnametmp,fname) != 0) {
	      if (errno == EXDEV) {
		      /* rename failed on cross-filesystem link.  
			 Copy the file instead. */
		      if (copy_file(fnametmp,fname, file->mode)) {
			      rprintf(FERROR,"copy %s -> %s : %s\n",
				      fnametmp,fname,strerror(errno));
		      } else {
			      set_perms(fname,file,NULL,0);
		      }
		      do_unlink(fnametmp);
	      } else {
		      rprintf(FERROR,"rename %s -> %s : %s\n",
			      fnametmp,fname,strerror(errno));
		      do_unlink(fnametmp);
	      }
      } else {
	      set_perms(fname,file,NULL,0);
      }

      cleanup_fname = NULL;


      if (!recv_ok) {
	      if (csum_length == SUM_LENGTH) {
		      rprintf(FERROR,"ERROR: file corruption in %s. File changed during transfer?\n",
			      fname);
	      } else {
		      if (verbose > 1)
			      rprintf(FINFO,"redoing %s(%d)\n",fname,i);
		      write_int(f_gen,i);
	      }
      }
    }

  if (preserve_hard_links)
