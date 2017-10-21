    }

    pid = do_cmd(shell_cmd,shell_machine,shell_user,shell_path,&f_in,&f_out);

    setup_protocol(f_out,f_in);

    setlinebuf(FINFO);
    setlinebuf(FERROR);

    if (verbose > 3) 
      fprintf(FERROR,"parent=%d child=%d sender=%d recurse=%d\n",
	      (int)getpid(),pid,sender,recurse);

    if (sender) {
