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

