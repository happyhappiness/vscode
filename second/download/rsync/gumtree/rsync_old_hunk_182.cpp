

static int do_recv(int f_in,int f_out,struct file_list *flist,char *local_name)
{
  int pid;
  int status=0;

  if (preserve_hard_links)
    init_hard_links(flist);

  if ((pid=fork()) == 0) {
    recv_files(f_in,flist,local_name);
    if (preserve_hard_links)
      do_hard_links(flist);
    if (verbose > 2)
      fprintf(FERROR,"receiver read %d\n",read_total());
    exit_cleanup(0);
  }

  generate_files(f_out,flist,local_name);

  waitpid(pid, &status, 0);

  return status;
}

