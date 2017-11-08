static void install_signal_handlers(void)
{
#ifdef SIGHUP
  /* ignore SIGHUP signal */
  if((old_sighup_handler = signal(SIGHUP, SIG_IGN)) == SIG_ERR)
    logmsg("cannot install SIGHUP handler: 5s", strerror(ERRNO));
#endif
#ifdef SIGPIPE
  /* ignore SIGPIPE signal */
  if((old_sigpipe_handler = signal(SIGPIPE, SIG_IGN)) == SIG_ERR)
    logmsg("cannot install SIGPIPE handler: 5s", strerror(ERRNO));
#endif
#ifdef SIGALRM
  /* ignore SIGALRM signal */
  if((old_sigalrm_handler = signal(SIGALRM, SIG_IGN)) == SIG_ERR)
    logmsg("cannot install SIGALRM handler: 5s", strerror(ERRNO));
#endif
#ifdef SIGINT
  /* handle SIGINT signal with our exit_signal_handler */
  if((old_sigint_handler = signal(SIGINT, exit_signal_handler)) == SIG_ERR)
    logmsg("cannot install SIGINT handler: 5s", strerror(ERRNO));
  else
    siginterrupt(SIGINT, 1);
#endif
#ifdef SIGTERM
  /* handle SIGTERM signal with our exit_signal_handler */
  if((old_sigterm_handler = signal(SIGTERM, exit_signal_handler)) == SIG_ERR)
    logmsg("cannot install SIGTERM handler: 5s", strerror(ERRNO));
  else
    siginterrupt(SIGTERM, 1);
#endif
}