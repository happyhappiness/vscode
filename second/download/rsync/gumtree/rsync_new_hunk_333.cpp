#if HAVE_SETLINEBUF
    setlinebuf(FINFO);
    setlinebuf(FERROR);
#endif

    if (verbose > 3) 
      fprintf(FINFO,"parent=%d child=%d sender=%d recurse=%d\n",
	      (int)getpid(),pid,sender,recurse);

    if (sender) {
      if (cvs_exclude)
	add_cvs_excludes();
      if (delete_mode) 
	send_exclude_list(f_out);
      flist = send_file_list(f_out,argc,argv);
      if (verbose > 3) 
	fprintf(FINFO,"file list sent\n");
      send_files(flist,f_out,f_in);
      if (verbose > 3)
	fprintf(FINFO,"waiting on %d\n",pid);
      waitpid(pid, &status, 0);
      report(-1);
      exit_cleanup(status);
    }

    send_exclude_list(f_out);

    flist = recv_file_list(f_in);
    if (!flist || flist->count == 0) {
      fprintf(FINFO,"nothing to do\n");
      exit_cleanup(0);
    }

    local_name = get_local_name(flist,argv[0]);

    status2 = do_recv(f_in,f_out,flist,local_name);
