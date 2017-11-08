static void sigpipe_ignore(struct SessionHandle *data,
                           struct sigpipe_ignore *ig)
{
  /* get a local copy of no_signal because the SessionHandle might not be
     around when we restore */
  ig->no_signal = data->set.no_signal;
  if(!data->set.no_signal) {
    struct sigaction action;
    /* first, extract the existing situation */
    memset(&ig->old_pipe_act, 0, sizeof(struct sigaction));
    sigaction(SIGPIPE, NULL, &ig->old_pipe_act);
    action = ig->old_pipe_act;
    /* ignore this signal */
    action.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &action, NULL);
  }
}