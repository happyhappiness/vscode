      pipe(from_child_pipe) < 0) {
    fprintf(FERROR,"pipe: %s\n",strerror(errno));
    exit_cleanup(1);
  }


  pid = fork();
  if (pid < 0) {
    fprintf(FERROR,"fork: %s\n",strerror(errno));
    exit_cleanup(1);
  }

  if (pid == 0)
