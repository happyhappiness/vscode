      }
      if (chdir(dir) != 0) {
	fprintf(stderr,"chdir %s : %s\n",dir,strerror(errno));
	continue;
      }
      flist_dir = dir;
      if (one_file_system)
	set_filesystem(fname);
      send_file_name(f,flist,recurse,fname);
      flist_dir = NULL;
      if (chdir(dbuf) != 0) {
	fprintf(stderr,"chdir %s : %s\n",dbuf,strerror(errno));
	exit(1);
      }
      continue;
    }

    if (one_file_system)
      set_filesystem(fname);
    send_file_name(f,flist,recurse,fname);
  }

  if (f != -1) {
    write_int(f,0);
    write_flush(f);
