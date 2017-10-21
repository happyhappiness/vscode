	  continue;
	}
      }

      /* move tmp file over real file */
      if (rename(fnametmp,fname) != 0) {
	      if (errno == EXDEV) {
		      /* rename failed on cross-filesystem link.  
			 Copy the file instead. */
		      if (copy_file(fnametmp,fname, file->mode)) {
			      fprintf(FERROR,"copy %s -> %s : %s\n",
				      fnametmp,fname,strerror(errno));
		      } else {
			      set_perms(fname,file,NULL,0);
		      }
		      unlink(fnametmp);
	      } else {
		      fprintf(FERROR,"rename %s -> %s : %s\n",
			      fnametmp,fname,strerror(errno));
		      unlink(fnametmp);
	      }
      } else {
	      set_perms(fname,file,NULL,0);
      }

      cleanup_fname = NULL;


      if (!recv_ok) {
	if (verbose > 1)
	  fprintf(FERROR,"redoing %s(%d)\n",fname,i);
        if (csum_length == SUM_LENGTH)
	  fprintf(FERROR,"ERROR: file corruption in %s\n",fname);
