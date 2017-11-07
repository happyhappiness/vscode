void mutt_unblock_signals_system (int catch)
{
  if (option (OPTSYSSIGNALSBLOCKED))
  {
    sigprocmask (SIG_UNBLOCK, &SigsetSys, NULL);
    if (catch)
    {
      sigaction (SIGQUIT, &SysOldQuit, NULL);
      sigaction (SIGINT, &SysOldInt, NULL);
    }
    else
    {
      struct sigaction sa;

      sa.sa_handler = SIG_DFL;
      sigemptyset (&sa.sa_mask);
      sa.sa_flags = 0;
      sigaction (SIGQUIT, &sa, NULL);
      sigaction (SIGINT, &sa, NULL);
    }

    unset_option (OPTSYSSIGNALSBLOCKED);
  }
}