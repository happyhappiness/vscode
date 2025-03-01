      exit(status);
    }

    send_exclude_list(f_out);

    flist = recv_file_list(f_in);
    if (!flist || flist->count == 0) {
      fprintf(stderr,"nothing to do\n");
      exit(0);
    }

    local_name = get_local_name(flist,argv[0]);

    if ((pid2=fork()) == 0) {
      recv_files(f_in,flist,local_name);
      if (verbose > 1)
	fprintf(stderr,"receiver read %d\n",read_total());
      exit(0);
    }

    generate_files(f_out,flist,local_name);

    waitpid(pid2, &status2, 0);

    report(f_in);

    waitpid(pid, &status, 0);

