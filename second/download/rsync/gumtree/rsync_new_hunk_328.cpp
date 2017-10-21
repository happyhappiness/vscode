  if (pipe(recv_pipe) < 0) {
    fprintf(FERROR,"pipe failed in do_recv\n");
    exit(1);
  }
  

  if ((pid=do_fork()) == 0) {
    recv_files(f_in,flist,local_name,recv_pipe[1]);
    if (verbose > 2)
      fprintf(FINFO,"receiver read %ld\n",(long)read_total());
    exit_cleanup(0);
  }

  generate_files(f_out,flist,local_name,recv_pipe[0]);

  waitpid(pid, &status, 0);
