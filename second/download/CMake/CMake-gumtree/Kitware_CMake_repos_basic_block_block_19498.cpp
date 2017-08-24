{
    uv__close(loop->signal_pipefd[1]);
    loop->signal_pipefd[1] = -1;
  }