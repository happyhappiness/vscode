void do_server_sender(int argc,char *argv[])
{
  int i;
  char *dir = argv[0];
  struct file_list *flist;

  if (verbose > 2)
    fprintf(FERROR,"server_sender starting pid=%d\n",(int)getpid());
  
  if (chdir(dir) != 0) {
    fprintf(FERROR,"chdir %s: %s\n",dir,strerror(errno));
    exit_cleanup(1);
  }
  argc--;
  argv++;
  
  if (strcmp(dir,".")) {
    int l = strlen(dir);
    if (strcmp(dir,"/") == 0) 
      l = 0;
    for (i=0;i<argc;i++)
      argv[i] += l+1;
  }

  if (argc == 0 && recurse) {
    argc=1;
    argv--;
    argv[0] = ".";
  }
    

  flist = send_file_list(STDOUT_FILENO,argc,argv);
  send_files(flist,STDOUT_FILENO,STDIN_FILENO);
  report(STDOUT_FILENO);
  exit_cleanup(0);
}