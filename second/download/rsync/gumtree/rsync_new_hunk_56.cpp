    if (chdir(dir) != 0) {
      fprintf(stderr,"chdir %s : %s\n",dir,strerror(errno));
      exit(1);
    }    
  }

  if (delete_mode)
    recv_exclude_list(STDIN_FILENO);

  flist = recv_file_list(STDIN_FILENO);
  if (!flist || flist->count == 0) {
    fprintf(stderr,"nothing to do\n");
    exit(1);
  }

