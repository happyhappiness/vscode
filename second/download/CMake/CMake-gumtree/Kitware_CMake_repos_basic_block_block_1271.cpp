{
        /* Use the error pipe to report the pid to the real parent.  */
        while ((write(si->ErrorPipe[1], &child_pid, sizeof(child_pid)) < 0) &&
               (errno == EINTR))
          ;

        /* Exit without cleanup.  The parent holds all resources.  */
        kwsysProcessExit();
        return 0; /* Never reached, but avoids SunCC warning.  */
      }