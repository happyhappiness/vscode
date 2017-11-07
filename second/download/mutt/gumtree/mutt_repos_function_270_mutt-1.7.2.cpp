void mutt_unblock_signals (void)
{
  if (option (OPTSIGNALSBLOCKED))
  {
    sigprocmask (SIG_UNBLOCK, &Sigset, 0);
    unset_option (OPTSIGNALSBLOCKED);
  }
}