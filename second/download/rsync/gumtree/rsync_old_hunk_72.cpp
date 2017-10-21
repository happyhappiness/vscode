      }
      fd2 = open(fnametmp,O_WRONLY|O_CREAT,st.st_mode);
      if (fd2 == -1) {
	fprintf(stderr,"open %s : %s\n",fnametmp,strerror(errno));
	return -1;
      }

      if (!am_server && verbose)
	printf("%s\n",fname);

      /* recv file data */
      receive_data(f_in,buf,fd2,fname);

      close(fd1);
      close(fd2);

      if (verbose > 2)
	fprintf(stderr,"renaming %s to %s\n",fnametmp,fname);

      if (make_backups) {
	char fnamebak[MAXPATHLEN];
	sprintf(fnamebak,"%s%s",fname,backup_suffix);
	if (rename(fname,fnamebak) != 0) {
	  fprintf(stderr,"rename %s %s : %s\n",fname,fnamebak,strerror(errno));
	  exit(1);
	}
      }

      /* move tmp file over real file */
      if (rename(fnametmp,fname) != 0) {
	fprintf(stderr,"rename %s -> %s : %s\n",
		fnametmp,fname,strerror(errno));
      }

      unmap_file(buf,st.st_size);

      set_perms(fname,&flist->files[i],NULL,0);
    }

  if (verbose > 2)
