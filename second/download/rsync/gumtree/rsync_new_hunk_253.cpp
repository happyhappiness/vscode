
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
