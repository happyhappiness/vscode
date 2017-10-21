  send_files(flist,STDOUT_FILENO,STDIN_FILENO);
  report(STDOUT_FILENO);
  exit_cleanup(0);
}


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


void do_server_recv(int argc,char *argv[])
{
  int status;
  char *dir = NULL;
  struct file_list *flist;
  char *local_name=NULL;
  
  if (verbose > 2)
    fprintf(FERROR,"server_recv(%d) starting pid=%d\n",argc,(int)getpid());

  if (argc > 0) {
    dir = argv[0];
    argc--;
    argv++;
    if (chdir(dir) != 0) {
      fprintf(FERROR,"chdir %s : %s\n",dir,strerror(errno));
      exit_cleanup(1);
    }    
  }

  if (delete_mode)
    recv_exclude_list(STDIN_FILENO);

  flist = recv_file_list(STDIN_FILENO);
  if (!flist || flist->count == 0) {
    fprintf(FERROR,"nothing to do\n");
    exit_cleanup(1);
  }

  if (argc > 0) {    
    if (strcmp(dir,".")) {
      argv[0] += strlen(dir);
      if (argv[0][0] == '/') argv[0]++;
    }
    local_name = get_local_name(flist,argv[0]);
  }

  status = do_recv(STDIN_FILENO,STDOUT_FILENO,flist,local_name);
  exit_cleanup(status);
}


static void usage(FILE *f)
{
