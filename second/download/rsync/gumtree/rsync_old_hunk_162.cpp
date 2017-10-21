	shell_user = shell_machine;
	shell_machine = p+1;
      }
    }

    if (verbose > 3) {
      fprintf(stderr,"cmd=%s machine=%s user=%s path=%s\n",
	      shell_cmd?shell_cmd:"",
	      shell_machine?shell_machine:"",
	      shell_user?shell_user:"",
	      shell_path?shell_path:"");
    }
    
    if (!sender && argc != 1) {
      usage(stderr);
      exit_cleanup(1);
    }

    pid = do_cmd(shell_cmd,shell_machine,shell_user,shell_path,&f_in,&f_out);

    write_int(f_out,PROTOCOL_VERSION);
    write_flush(f_out);
    {
      remote_version = read_int(f_in);
      if (remote_version < MIN_PROTOCOL_VERSION ||
	  remote_version > MAX_PROTOCOL_VERSION) {
	fprintf(stderr,"protocol version mismatch - is your shell clean?\n");
	exit_cleanup(1);
      }	
    }

    setup_protocol();

    if (verbose > 3) 
      fprintf(stderr,"parent=%d child=%d sender=%d recurse=%d\n",
	      (int)getpid(),pid,sender,recurse);

    if (sender) {
      if (cvs_exclude)
	add_cvs_excludes();
      if (delete_mode) 
	send_exclude_list(f_out);
      flist = send_file_list(f_out,recurse,argc,argv);
      if (verbose > 3) 
	fprintf(stderr,"file list sent\n");
      send_files(flist,f_out,f_in);
      if (verbose > 3)
	fprintf(stderr,"waiting on %d\n",pid);
      waitpid(pid, &status, 0);
      report(-1);
      exit_cleanup(status);
    }

    send_exclude_list(f_out);

    flist = recv_file_list(f_in);
    if (!flist || flist->count == 0) {
      fprintf(stderr,"nothing to do\n");
      exit_cleanup(0);
    }

    local_name = get_local_name(flist,argv[0]);

    if ((pid2=fork()) == 0) {
      recv_files(f_in,flist,local_name);
      if (verbose > 1)
	fprintf(stderr,"receiver read %d\n",read_total());
      exit_cleanup(0);
    }

    generate_files(f_out,flist,local_name);

    waitpid(pid2, &status2, 0);

    report(f_in);

    waitpid(pid, &status, 0);

    return status | status2;
