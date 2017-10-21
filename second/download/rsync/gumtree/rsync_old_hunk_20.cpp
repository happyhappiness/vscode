      exit(status);
    }

    send_exclude_list(f_out);

    flist = recv_file_list(f_in);
    if (flist->count == 0) {
      exit(0);
    }

    {
      struct stat st;
      if (stat(argv[0],&st) != 0) {
	if (mkdir(argv[0],0777) != 0) {
	  fprintf(stderr,"mkdir %s : %s\n",argv[0],strerror(errno));
	  exit(1);
	}
	stat(argv[0],&st);
      }
      
      if (S_ISDIR(st.st_mode)) {
	if (chdir(argv[0]) != 0) {
	  fprintf(stderr,"chdir %s : %s\n",argv[0],strerror(errno));
	  exit(1);
	}
      } else {
	local_name = argv[0];
      }
    }


    if ((pid2=fork()) == 0) {
      recv_files(f_in,flist,local_name);
      if (verbose > 1)
	fprintf(stderr,"receiver read %d\n",read_total());
      exit(0);
    }

    for (i = 0; i < flist->count; i++) {
      if (S_ISDIR(flist->files[i].mode)) {
	if (dry_run) continue;
	if (mkdir(flist->files[i].name,flist->files[i].mode) != 0 &&
	    errno != EEXIST) {
	  fprintf(stderr,"mkdir %s : %s\n",
		  flist->files[i].name,strerror(errno));
	}
	continue;
      }
      recv_generator(local_name?local_name:flist->files[i].name,
		     flist,i,f_out);
    }
    write_int(f_out,-1);
    write_flush(f_out);
    if (verbose > 1)
      fprintf(stderr,"generator wrote %d\n",write_total());
    
    waitpid(pid2, &status2, 0);

    report(f_in);

    waitpid(pid, &status, 0);

