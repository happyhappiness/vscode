void mutt_allow_interrupt (int disposition)
{
  struct sigaction sa;
  
  memset (&sa, 0, sizeof sa);
  sa.sa_handler = sighandler;
#ifdef SA_RESTART
  if (disposition == 0)
    sa.sa_flags |= SA_RESTART;
#endif
  sigaction (SIGINT, &sa, NULL);
}