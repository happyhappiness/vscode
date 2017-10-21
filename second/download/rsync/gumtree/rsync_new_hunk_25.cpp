    fprintf(stderr,"server_recv(%d) starting pid=%d\n",argc,(int)getpid());

  if (argc > 0) {
    dir = argv[0];
    argc--;
    argv++;
    if (chdir(dir) != 0) {
      fprintf(stderr,"chdir %s : %s\n",dir,strerror(errno));
      exit(1);
    }    
  }

  flist = recv_file_list(STDIN_FILENO);
  if (!flist || flist->count == 0) {
    fprintf(stderr,"nothing to do\n");
    exit(1);
  }

  if (argc > 0) {    
    if (strcmp(dir,".")) {
      argv[0] += strlen(dir);
      if (argv[0][0] == '/') argv[0]++;
    }
    local_name = get_local_name(flist,argv[0]);
  }

  if ((pid=fork()) == 0) {
    recv_files(STDIN_FILENO,flist,local_name);
    if (verbose > 2)
      fprintf(stderr,"receiver read %d\n",read_total());
    exit(0);
  }

  generate_files(STDOUT_FILENO,flist,local_name);

