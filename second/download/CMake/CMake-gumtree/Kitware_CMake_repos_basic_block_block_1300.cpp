((sigaction(SIGCHLD, &kwsysProcessesOldSigChldAction, 0) < 0) &&
               (errno == EINTR))
          ;