      }
      strcat(fname,flist->files[i].name);

      if (verbose > 2) 
	fprintf(stderr,"send_files(%d,%s)\n",i,fname);

      fd = open(fname,O_RDONLY);
      if (fd == -1) {
	fprintf(stderr,"send_files failed to open %s: %s\n",
		fname,strerror(errno));
	return -1;
      }
