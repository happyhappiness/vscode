
      fname = flist->files[i].name;

      if (local_name)
	fname = local_name;

      if (dry_run) {
	if (!am_server && verbose)
	  printf("%s\n",fname);
	continue;
      }

      if (verbose > 2)
	fprintf(stderr,"recv_files(%s)\n",fname);

      /* open the file */  
      fd1 = open(fname,O_RDONLY|O_CREAT,flist->files[i].mode);

