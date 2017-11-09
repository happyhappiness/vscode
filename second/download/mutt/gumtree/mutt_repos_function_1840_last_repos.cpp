pid_t
mutt_create_filter_fd (const char *cmd, FILE **in, FILE **out, FILE **err,
		       int fdin, int fdout, int fderr)
{
  int pin[2], pout[2], perr[2], thepid;
  char columns[11];

  if (in)
  {
    *in = 0;
    if (pipe (pin) == -1)
      return (-1);
  }

  if (out)
  {
    *out = 0;
    if (pipe (pout) == -1)
    {
      if (in)
      {
	close (pin[0]);
	close (pin[1]);
      }
      return (-1);
    }
  }

  if (err)
  {
    *err = 0;
    if (pipe (perr) == -1)
    {
      if (in)
      {
	close (pin[0]);
	close (pin[1]);
      }
      if (out)
      {
	close (pout[0]);
	close (pout[1]);
      }
      return (-1);
    }
  }

  mutt_block_signals_system ();

  if ((thepid = fork ()) == 0)
  {
    mutt_unblock_signals_system (0);

    if (in)
    {
      close (pin[1]);
      dup2 (pin[0], 0);
      close (pin[0]);
    }
    else if (fdin != -1)
    {
      dup2 (fdin, 0);
      close (fdin);
    }

    if (out)
    {
      close (pout[0]);
      dup2 (pout[1], 1);
      close (pout[1]);
    }
    else if (fdout != -1)
    {
      dup2 (fdout, 1);
      close (fdout);
    }

    if (err)
    {
      close (perr[0]);
      dup2 (perr[1], 2);
      close (perr[1]);
    }
    else if (fderr != -1)
    {
      dup2 (fderr, 2);
      close (fderr);
    }

    if (MuttIndexWindow && (MuttIndexWindow->cols > 0))
    {
      snprintf (columns, sizeof (columns), "%d", MuttIndexWindow->cols);
      mutt_envlist_set ("COLUMNS", columns, 1);
    }

    execle (EXECSHELL, "sh", "-c", cmd, NULL, mutt_envlist ());
    _exit (127);
  }
  else if (thepid == -1)
  {
    mutt_unblock_signals_system (1);

    if (in)
    {
      close (pin[0]);
      close (pin[1]);
    }
    
    if (out)
    {
      close (pout[0]);
      close (pout[1]);
    }

    if (err)
    {
      close (perr[0]);
      close (perr[1]);
    }

    return (-1);
  }

  if (out)
  {
    close (pout[1]);
    *out = fdopen (pout[0], "r");
  }

  if (in)
  {
    close (pin[0]);
    *in = fdopen (pin[1], "w");
  }

  if (err)
  {
    close (perr[1]);
    *err = fdopen (perr[0], "r");
  }

  return (thepid);
}