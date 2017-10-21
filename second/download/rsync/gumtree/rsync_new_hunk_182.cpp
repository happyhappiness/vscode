

static int do_recv(int f_in,int f_out,struct file_list *flist,char *local_name)
{
  int pid;
  int status=0;
  int recv_pipe[2];

  if (preserve_hard_links)
    init_hard_links(flist);

  if (pipe(recv_pipe) < 0) {
    fprintf(FERROR,"pipe failed in do_recv\n");
    exit(1);
  }
  

  if ((pid=fork()) == 0) {
    recv_files(f_in,flist,local_name,recv_pipe[1]);
    if (preserve_hard_links)
      do_hard_links(flist);
    if (verbose > 2)
      fprintf(FERROR,"receiver read %d\n",read_total());
    exit_cleanup(0);
  }

  generate_files(f_out,flist,local_name,recv_pipe[0]);

  waitpid(pid, &status, 0);

  return status;
}

