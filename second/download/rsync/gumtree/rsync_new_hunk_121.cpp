  if (argc > 0) {
    dir = argv[0];
    argc--;
    argv++;
    if (chdir(dir) != 0) {
      fprintf(stderr,"chdir %s : %s\n",dir,strerror(errno));
      exit_cleanup(1);
    }    
  }

  if (delete_mode)
    recv_exclude_list(STDIN_FILENO);

  flist = recv_file_list(STDIN_FILENO);
  if (!flist || flist->count == 0) {
    fprintf(stderr,"nothing to do\n");
    exit_cleanup(1);
  }

  if (argc > 0) {    
    if (strcmp(dir,".")) {
      argv[0] += strlen(dir);
      if (argv[0][0] == '/') argv[0]++;
