
      if (make_backups) {
	char fnamebak[MAXPATHLEN];
	sprintf(fnamebak,"%s%s",fname,backup_suffix);
	if (rename(fname,fnamebak) != 0 && errno != ENOENT) {
	  fprintf(FERROR,"rename %s %s : %s\n",fname,fnamebak,strerror(errno));
	  continue;
	}
      }

      /* move tmp file over real file */
      if (rename(fnametmp,fname) != 0) {
	fprintf(FERROR,"rename %s -> %s : %s\n",
		fnametmp,fname,strerror(errno));
	unlink(fnametmp);
      }

      cleanup_fname = NULL;

      set_perms(fname,file,NULL,0);

