void mutt_block_signals_system (void)
{
  struct sigaction sa;

  if (! option (OPTSYSSIGNALSBLOCKED))
  {
    /* POSIX: ignore SIGINT and SIGQUIT & block SIGCHLD  before exec */
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    sigemptyset (&sa.sa_mask);
    sigaction (SIGINT, &sa, &SysOldInt);
    sigaction (SIGQUIT, &sa, &SysOldQuit);

    sigemptyset (&SigsetSys);
    sigaddset (&SigsetSys, SIGCHLD);
    sigprocmask (SIG_BLOCK, &SigsetSys, 0);
    set_option (OPTSYSSIGNALSBLOCKED);
  }
}