{
    struct sigaction action;
    /* first, extract the existing situation */
    memset(&ig->old_pipe_act, 0, sizeof(struct sigaction));
    sigaction(SIGPIPE, NULL, &ig->old_pipe_act);
    action = ig->old_pipe_act;
    /* ignore this signal */
    action.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &action, NULL);
  }