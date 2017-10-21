  char *dir = argv[0];
  struct file_list *flist;

  if (verbose > 2)
    fprintf(FERROR,"server_sender starting pid=%d\n",(int)getpid());
  
  if (!relative_paths && chdir(dir) != 0) {
    fprintf(FERROR,"chdir %s: %s (3)\n",dir,strerror(errno));
    exit_cleanup(1);
  }
  argc--;
  argv++;
  
  if (strcmp(dir,".")) {
