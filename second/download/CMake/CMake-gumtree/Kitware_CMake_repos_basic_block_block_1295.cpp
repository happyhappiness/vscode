{

    /* Make sure there is enough space for the new signal pipe.  */
    kwsysProcessInstances oldProcesses = kwsysProcesses;
    kwsysProcessInstances newProcesses = oldProcesses;
    if (oldProcesses.Count == oldProcesses.Size) {
      /* Start with enough space for a small number of process instances
         and double the size each time more is needed.  */
      newProcesses.Size = oldProcesses.Size ? oldProcesses.Size * 2 : 4;

      /* Try allocating the new block of memory.  */
      if ((newProcesses.Processes = ((kwsysProcess**)malloc(
             (size_t)(newProcesses.Size) * sizeof(kwsysProcess*))))) {
        /* Copy the old pipe set to the new memory.  */
        if (oldProcesses.Count > 0) {
          memcpy(newProcesses.Processes, oldProcesses.Processes,
                 ((size_t)(oldProcesses.Count) * sizeof(kwsysProcess*)));
        }
      } else {
        /* Failed to allocate memory for the new signal pipe set.  */
        return 0;
      }
    }

    /* Append the new signal pipe to the set.  */
    newProcesses.Processes[newProcesses.Count++] = cp;

    /* Store the new set in that seen by the signal handler.  */
    kwsysProcessesUpdate(&newProcesses);

    /* Free the original pipes if new ones were allocated.  */
    if (newProcesses.Processes != oldProcesses.Processes) {
      free(oldProcesses.Processes);
    }

    /* If this is the first process, enable the signal handler.  */
    if (newProcesses.Count == 1) {
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
  }