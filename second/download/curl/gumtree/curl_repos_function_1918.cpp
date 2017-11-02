static void sigpipe_restore(struct sigpipe_ignore *ig)
{
  if(!ig->no_signal)
    /* restore the outside state */
    sigaction(SIGPIPE, &ig->old_pipe_act, NULL);
}