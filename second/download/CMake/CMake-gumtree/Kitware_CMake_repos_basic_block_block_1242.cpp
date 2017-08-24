{
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