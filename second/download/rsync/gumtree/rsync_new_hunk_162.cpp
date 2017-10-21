	shell_user = shell_machine;
	shell_machine = p+1;
      }
    }

    if (verbose > 3) {
      fprintf(FERROR,"cmd=%s machine=%s user=%s path=%s\n",
	      shell_cmd?shell_cmd:"",
	      shell_machine?shell_machine:"",
	      shell_user?shell_user:"",
	      shell_path?shell_path:"");
    }
    
    if (!sender && argc != 1) {
      usage(FERROR);
      exit_cleanup(1);
    }

    pid = do_cmd(shell_cmd,shell_machine,shell_user,shell_path,&f_in,&f_out);

    setup_protocol(f_out,f_in);

    if (verbose > 3) 
      fprintf(FERROR,"parent=%d child=%d sender=%d recurse=%d\n",
	      (int)getpid(),pid,sender,recurse);

    if (sender) {
      if (cvs_exclude)
	add_cvs_excludes();
      if (delete_mode) 
	send_exclude_list(f_out);
      flist = send_file_list(f_out,recurse,argc,argv);
      if (verbose > 3) 
	fprintf(FERROR,"file list sent\n");
      send_files(flist,f_out,f_in);
      if (verbose > 3)
	fprintf(FERROR,"waiting on %d\n",pid);
      waitpid(pid, &status, 0);
      report(-1);
      exit_cleanup(status);
    }

    send_exclude_list(f_out);

    flist = recv_file_list(f_in);
    if (!flist || flist->count == 0) {
      fprintf(FERROR,"nothing to do\n");
      exit_cleanup(0);
    }

    local_name = get_local_name(flist,argv[0]);

    status2 = do_recv(f_in,f_out,flist,local_name);

    report(f_in);

    waitpid(pid, &status, 0);

    return status | status2;
