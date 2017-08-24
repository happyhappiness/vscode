{
      /* Install our handler for SIGCHLD.  Repeat call until it is not
         interrupted.  */
      struct sigaction newSigAction;
      memset(&newSigAction, 0, sizeof(struct sigaction));
#if KWSYSPE_USE_SIGINFO
      newSigAction.sa_sigaction = kwsysProcessesSignalHandler;
      newSigAction.sa_flags = SA_NOCLDSTOP | SA_SIGINFO;
#ifdef SA_RESTART
      newSigAction.sa_flags |= SA_RESTART;
#endif
#else
      newSigAction.sa_handler = kwsysProcessesSignalHandler;
      newSigAction.sa_flags = SA_NOCLDSTOP;
#endif
      sigemptyset(&newSigAction.sa_mask);
      while ((sigaction(SIGCHLD, &newSigAction,
                        &kwsysProcessesOldSigChldAction) < 0) &&
             (errno == EINTR))
        ;

      /* Install our handler for SIGINT / SIGTERM.  Repeat call until
         it is not interrupted.  */
      sigemptyset(&newSigAction.sa_mask);
      sigaddset(&newSigAction.sa_mask, SIGTERM);
      while ((sigaction(SIGINT, &newSigAction,
                        &kwsysProcessesOldSigIntAction) < 0) &&
             (errno == EINTR))
        ;

      sigemptyset(&newSigAction.sa_mask);
      sigaddset(&newSigAction.sa_mask, SIGINT);
      while ((sigaction(SIGTERM, &newSigAction,
                        &kwsysProcessesOldSigIntAction) < 0) &&
             (errno == EINTR))
        ;
    }