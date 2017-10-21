      }

      file = &flist->files[i];

      fname[0] = 0;
      if (file->dir) {
	strcpy(fname,file->dir);
	strcat(fname,"/");
      }
      strcat(fname,file->name);

      if (verbose > 2) 
	fprintf(FERROR,"send_files(%d,%s)\n",i,fname);

      if (dry_run) {	
	if (!am_server && verbose)
