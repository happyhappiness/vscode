{
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