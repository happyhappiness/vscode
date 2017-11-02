static void install_signal_handlers(void)
{
#ifdef SIGHUP
  /* ignore SIGHUP signal */
  if((old_sighup_handler = signal(SIGHUP, SIG_IGN)) == SIG_ERR)
    logmsg("cannot install SIGHUP handler: %s", strerror(errno));
#endif
#ifdef SIGPIPE
  /* ignore SIGPIPE signal */
  if((old_sigpipe_handler = signal(SIGPIPE, SIG_IGN)) == SIG_ERR)
    logmsg("cannot install SIGPIPE handler: %s", strerror(errno));
#endif
#ifdef SIGINT
  /* handle SIGINT signal with our exit_signal_handler */
  if((old_sigint_handler = signal(SIGINT, exit_signal_handler)) == SIG_ERR)
    logmsg("cannot install SIGINT handler: %s", strerror(errno));
  else
    siginterrupt(SIGINT, 1);
#endif
#ifdef SIGTERM
  /* handle SIGTERM signal with our exit_signal_handler */
  if((old_sigterm_handler = signal(SIGTERM, exit_signal_handler)) == SIG_ERR)
    logmsg("cannot install SIGTERM handler: %s", strerror(errno));
  else
    siginterrupt(SIGTERM, 1);
#endif
#if defined(SIGBREAK) && defined(WIN32)
  /* handle SIGBREAK signal with our exit_signal_handler */
  if((old_sigbreak_handler = signal(SIGBREAK, exit_signal_handler)) == SIG_ERR)
    logmsg("cannot install SIGBREAK handler: %s", strerror(errno));
  else
    siginterrupt(SIGBREAK, 1);
#endif
}