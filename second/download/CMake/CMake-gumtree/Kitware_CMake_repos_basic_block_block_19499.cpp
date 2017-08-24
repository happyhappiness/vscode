{
    uv__close(loop->signal_pipefd[0]);
    loop->signal_pipefd[0] = -1;
  }