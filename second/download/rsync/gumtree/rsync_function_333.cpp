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
      fprintf(FERROR,"chdir %s : %s (4)\n",dir,strerror(errno));
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