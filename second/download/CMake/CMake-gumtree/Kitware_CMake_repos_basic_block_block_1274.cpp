(middle_pid < 0) {
      /* Fork failed.  Return as if we were not detaching.  */
      return middle_pid;
    } else if (middle_pid == 0) {
      /* This is the intermediate process.  Create the real child.  */
      pid_t child_pid = fork();
      if (child_pid == 0) {
        /* This is the real child process.  There is nothing to do here.  */
        return 0;
      } else {
        /* Use the error pipe to report the pid to the real parent.  */
        while ((write(si->ErrorPipe[1], &child_pid, sizeof(child_pid)) < 0) &&
               (errno == EINTR))
          ;

        /* Exit without cleanup.  The parent holds all resources.  */
        kwsysProcessExit();
        return 0; /* Never reached, but avoids SunCC warning.  */
      }
    } else {
      /* This is the original parent process.  The intermediate
         process will use the error pipe to report the pid of the
         detached child.  */
      pid_t child_pid;
      int status;
      while ((read(si->ErrorPipe[0], &child_pid, sizeof(child_pid)) < 0) &&
             (errno == EINTR))
        ;

      /* Wait for the intermediate process to exit and clean it up.  */
      while ((waitpid(middle_pid, &status, 0) < 0) && (errno == EINTR))
        ;
      return child_pid;
    }