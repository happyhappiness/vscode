static int
send_msg (const char *path, char **args, const char *msg, char **tempfile)
{
  sigset_t set;
  int fd, st;
  pid_t pid, ppid;

  mutt_block_signals_system ();

  sigemptyset (&set);
  /* we also don't want to be stopped right now */
  sigaddset (&set, SIGTSTP);
  sigprocmask (SIG_BLOCK, &set, NULL);

  if (SendmailWait >= 0 && tempfile)
  {
    char tmp[_POSIX_PATH_MAX];

    mutt_mktemp (tmp, sizeof (tmp));
    *tempfile = safe_strdup (tmp);
  }

  if ((pid = fork ()) == 0)
  {
    struct sigaction act, oldalrm;

    /* save parent's ID before setsid() */
    ppid = getppid ();

    /* we want the delivery to continue even after the main process dies,
     * so we put ourselves into another session right away
     */
    setsid ();

    /* next we close all open files */
    close (0);
#if defined(OPEN_MAX)
    for (fd = tempfile ? 1 : 3; fd < OPEN_MAX; fd++)
      close (fd);
#elif defined(_POSIX_OPEN_MAX)
    for (fd = tempfile ? 1 : 3; fd < _POSIX_OPEN_MAX; fd++)
      close (fd);
#else
    if (tempfile)
    {
      close (1);
      close (2);
    }
#endif

    /* now the second fork() */
    if ((pid = fork ()) == 0)
    {
      /* "msg" will be opened as stdin */
      if (open (msg, O_RDONLY, 0) < 0)
      {
	unlink (msg);
	_exit (S_ERR);
      }
      unlink (msg);

      if (SendmailWait >= 0 && tempfile && *tempfile)
      {
	/* *tempfile will be opened as stdout */
	if (open (*tempfile, O_WRONLY | O_APPEND | O_CREAT | O_EXCL, 0600) < 0)
	  _exit (S_ERR);
	/* redirect stderr to *tempfile too */
	if (dup (1) < 0)
	  _exit (S_ERR);
      }
      else if (tempfile)
      {
	if (open ("/dev/null", O_WRONLY | O_APPEND) < 0)	/* stdout */
	  _exit (S_ERR);
	if (open ("/dev/null", O_RDWR | O_APPEND) < 0)		/* stderr */
	  _exit (S_ERR);
      }

      execvp (path, args);
      _exit (S_ERR);
    }
    else if (pid == -1)
    {
      unlink (msg);
      if (tempfile)
	FREE (tempfile);		/* __FREE_CHECKED__ */
      _exit (S_ERR);
    }

    /* SendmailWait > 0: interrupt waitpid() after SendmailWait seconds
     * SendmailWait = 0: wait forever
     * SendmailWait < 0: don't wait
     */
    if (SendmailWait > 0)
    {
      SigAlrm = 0;
      act.sa_handler = alarm_handler;
#ifdef SA_INTERRUPT
      /* need to make sure waitpid() is interrupted on SIGALRM */
      act.sa_flags = SA_INTERRUPT;
#else
      act.sa_flags = 0;
#endif
      sigemptyset (&act.sa_mask);
      sigaction (SIGALRM, &act, &oldalrm);
      alarm (SendmailWait);
    }
    else if (SendmailWait < 0)
      _exit (0xff & EX_OK);

    if (waitpid (pid, &st, 0) > 0)
    {
      st = WIFEXITED (st) ? WEXITSTATUS (st) : S_ERR;
      if (SendmailWait && st == (0xff & EX_OK) && tempfile && *tempfile)
      {
	unlink (*tempfile); /* no longer needed */
	FREE (tempfile);		/* __FREE_CHECKED__ */
      }
    }
    else
    {
      st = (SendmailWait > 0 && errno == EINTR && SigAlrm) ?
	      S_BKG : S_ERR;
      if (SendmailWait > 0 && tempfile && *tempfile)
      {
	unlink (*tempfile);
	FREE (tempfile);		/* __FREE_CHECKED__ */
      }
    }

    /* reset alarm; not really needed, but... */
    alarm (0);
    sigaction (SIGALRM, &oldalrm, NULL);

    if (kill (ppid, 0) == -1 && errno == ESRCH && tempfile && *tempfile)
    {
      /* the parent is already dead */
      unlink (*tempfile);
      FREE (tempfile);		/* __FREE_CHECKED__ */
    }

    _exit (st);
  }

  sigprocmask (SIG_UNBLOCK, &set, NULL);

  if (pid != -1 && waitpid (pid, &st, 0) > 0)
    st = WIFEXITED (st) ? WEXITSTATUS (st) : S_ERR; /* return child status */
  else
    st = S_ERR;	/* error */

  mutt_unblock_signals_system (1);

  return (st);
}