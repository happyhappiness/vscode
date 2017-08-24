{
  sigset_t mask, old_mask;
  int pgidPipe[2];
  char tmp;
  ssize_t readRes;

  /* Create the error reporting pipe.  */
  if (pipe(si->ErrorPipe) < 0) {
    return 0;
  }

  /* Create a pipe for detecting that the child process has created a process
     group and session.  */
  if (pipe(pgidPipe) < 0) {
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[0]);
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[1]);
    return 0;
  }

  /* Set close-on-exec flag on the pipe's write end.  */
  if (fcntl(si->ErrorPipe[1], F_SETFD, FD_CLOEXEC) < 0 ||
      fcntl(pgidPipe[1], F_SETFD, FD_CLOEXEC) < 0) {
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[0]);
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[1]);
    kwsysProcessCleanupDescriptor(&pgidPipe[0]);
    kwsysProcessCleanupDescriptor(&pgidPipe[1]);
    return 0;
  }

  /* Block SIGINT / SIGTERM while we start.  The purpose is so that our signal
     handler doesn't get called from the child process after the fork and
     before the exec, and subsequently start kill()'ing PIDs from ForkPIDs. */
  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);
  sigaddset(&mask, SIGTERM);
  if (sigprocmask(SIG_BLOCK, &mask, &old_mask) < 0) {
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[0]);
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[1]);
    kwsysProcessCleanupDescriptor(&pgidPipe[0]);
    kwsysProcessCleanupDescriptor(&pgidPipe[1]);
    return 0;
  }

/* Fork off a child process.  */
#if defined(__VMS)
  /* VMS needs vfork and execvp to be in the same function because
     they use setjmp/longjmp to run the child startup code in the
     parent!  TODO: OptionDetach.  Also
     TODO:  CreateProcessGroup.  */
  cp->ForkPIDs[prIndex] = vfork();
#else
  cp->ForkPIDs[prIndex] = kwsysProcessFork(cp, si);
#endif
  if (cp->ForkPIDs[prIndex] < 0) {
    sigprocmask(SIG_SETMASK, &old_mask, 0);
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[0]);
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[1]);
    kwsysProcessCleanupDescriptor(&pgidPipe[0]);
    kwsysProcessCleanupDescriptor(&pgidPipe[1]);
    return 0;
  }

  if (cp->ForkPIDs[prIndex] == 0) {
#if defined(__VMS)
    /* Specify standard pipes for child process.  */
    decc$set_child_standard_streams(si->StdIn, si->StdOut, si->StdErr);
#else
    /* Close the read end of the error reporting / process group
       setup pipe.  */
    close(si->ErrorPipe[0]);
    close(pgidPipe[0]);

    /* Setup the stdin, stdout, and stderr pipes.  */
    if (si->StdIn > 0) {
      dup2(si->StdIn, 0);
    } else if (si->StdIn < 0) {
      close(0);
    }
    if (si->StdOut != 1) {
      dup2(si->StdOut, 1);
    }
    if (si->StdErr != 2) {
      dup2(si->StdErr, 2);
    }

    /* Clear the close-on-exec flag for stdin, stdout, and stderr.
       All other pipe handles will be closed when exec succeeds.  */
    fcntl(0, F_SETFD, 0);
    fcntl(1, F_SETFD, 0);
    fcntl(2, F_SETFD, 0);

    /* Restore all default signal handlers. */
    kwsysProcessRestoreDefaultSignalHandlers();

    /* Now that we have restored default signal handling and created the
       process group, restore mask.  */
    sigprocmask(SIG_SETMASK, &old_mask, 0);

    /* Create new process group.  We use setsid instead of setpgid to avoid
       the child getting hung up on signals like SIGTTOU.  (In the real world,
       this has been observed where "git svn" ends up calling the "resize"
       program which opens /dev/tty.  */
    if (cp->CreateProcessGroup && setsid() < 0) {
      kwsysProcessChildErrorExit(si->ErrorPipe[1]);
    }
#endif

    /* Execute the real process.  If successful, this does not return.  */
    execvp(cp->Commands[prIndex][0], cp->Commands[prIndex]);
    /* TODO: What does VMS do if the child fails to start?  */
    /* TODO: On VMS, how do we put the process in a new group?  */

    /* Failure.  Report error to parent and terminate.  */
    kwsysProcessChildErrorExit(si->ErrorPipe[1]);
  }

#if defined(__VMS)
  /* Restore the standard pipes of this process.  */
  decc$set_child_standard_streams(0, 1, 2);
#endif

  /* We are done with the error reporting pipe and process group setup pipe
     write end.  */
  kwsysProcessCleanupDescriptor(&si->ErrorPipe[1]);
  kwsysProcessCleanupDescriptor(&pgidPipe[1]);

  /* Make sure the child is in the process group before we proceed.  This
     avoids race conditions with calls to the kill function that we make for
     signalling process groups.  */
  while ((readRes = read(pgidPipe[0], &tmp, 1)) > 0)
    ;
  if (readRes < 0) {
    sigprocmask(SIG_SETMASK, &old_mask, 0);
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[0]);
    kwsysProcessCleanupDescriptor(&pgidPipe[0]);
    return 0;
  }
  kwsysProcessCleanupDescriptor(&pgidPipe[0]);

  /* Unmask signals.  */
  if (sigprocmask(SIG_SETMASK, &old_mask, 0) < 0) {
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[0]);
    return 0;
  }

  /* A child has been created.  */
  ++cp->CommandsLeft;

  /* Block until the child's exec call succeeds and closes the error
     pipe or writes data to the pipe to report an error.  */
  {
    kwsysProcess_ssize_t total = 0;
    kwsysProcess_ssize_t n = 1;
    /* Read the entire error message up to the length of our buffer.  */
    while (total < KWSYSPE_PIPE_BUFFER_SIZE && n > 0) {
      /* Keep trying to read until the operation is not interrupted.  */
      while (((n = read(si->ErrorPipe[0], cp->ErrorMessage + total,
                        (size_t)(KWSYSPE_PIPE_BUFFER_SIZE - total))) < 0) &&
             (errno == EINTR))
        ;
      if (n > 0) {
        total += n;
      }
    }

    /* We are done with the error reporting pipe read end.  */
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[0]);

    if (total > 0) {
      /* The child failed to execute the process.  */
      return 0;
    }
  }

  return 1;
}