  if (reyes_ok)
    regfree (& reyes);
  if (reno_ok)
    regfree (& reno);
#endif

  if (def != -1)
  {
    addstr ((char *) (def == M_YES ? yes : no));
    mutt_refresh ();
  }
  else
  {
    /* when the users cancels with ^G, clear the message stored with
     * mutt_message() so it isn't displayed when the screen is refreshed. */
    mutt_clear_error();
  }
  return (def);
}

/* this function is called when the user presses the abort key */
void mutt_query_exit (void)
{
  mutt_flushinp ();
  curs_set (1);
  if (Timeout)
    timeout (-1); /* restore blocking operation */
  if (mutt_yesorno (_("Exit Mutt?"), M_YES) == M_YES)
  {
    endwin ();
    exit (1);
  }
  mutt_clear_error();
  mutt_curs_set (-1);
  SigInt = 0;
}

static void curses_message (int error, const char *fmt, va_list ap)
{
  char scratch[LONG_STRING];

  vsnprintf (scratch, sizeof (scratch), fmt, ap);

  dprint (1, (debugfile, "%s\n", scratch));
  mutt_format_string (Errorbuf, sizeof (Errorbuf),
		      0, COLS, FMT_LEFT, 0, scratch, sizeof (scratch), 0);

  if (!option (OPTKEEPQUIET))
  {
    if (error)
      BEEP ();
    SETCOLOR (error ? MT_COLOR_ERROR : MT_COLOR_MESSAGE);
    mvaddstr (LINES-1, 0, Errorbuf);
    NORMAL_COLOR;
    clrtoeol ();
    mutt_refresh ();
  }

  if (error)
    set_option (OPTMSGERR);
  else
    unset_option (OPTMSGERR);
}

void mutt_curses_error (const char *fmt, ...)
{
  va_list ap;

  va_start (ap, fmt);
  curses_message (1, fmt, ap);
  va_end (ap);
}

void mutt_curses_message (const char *fmt, ...)
{
  va_list ap;

  va_start (ap, fmt);
  curses_message (0, fmt, ap);
  va_end (ap);
}

void mutt_progress_init (progress_t* progress, const char *msg,
			 unsigned short flags, unsigned short inc,
			 long size)
{
  struct timeval tv = { 0, 0 };

  if (!progress)
    return;
  if (option(OPTNOCURSES))
    return;

  memset (progress, 0, sizeof (progress_t));
  progress->inc = inc;
  progress->flags = flags;
  progress->msg = msg;
  progress->size = size;
  if (progress->size) {
    if (progress->flags & M_PROGRESS_SIZE)
      mutt_pretty_size (progress->sizestr, sizeof (progress->sizestr),
			progress->size);
    else
      snprintf (progress->sizestr, sizeof (progress->sizestr), "%ld",
		progress->size);
  }
  if (!inc)
  {
    if (size)
      mutt_message ("%s (%s)", msg, progress->sizestr);
    else
      mutt_message (msg);
    return;
  }
  if (gettimeofday (&tv, NULL) < 0)
    dprint (1, (debugfile, "gettimeofday failed: %d\n", errno));
  /* if timestamp is 0 no time-based suppression is done */
  if (TimeInc)
    progress->timestamp = ((unsigned int) tv.tv_sec * 1000)
        + (unsigned int) (tv.tv_usec / 1000);
  mutt_progress_update (progress, 0, 0);
}

void mutt_progress_update (progress_t* progress, long pos, int percent)
{
  char posstr[SHORT_STRING];
  short update = 0;
  struct timeval tv = { 0, 0 };
  unsigned int now = 0;

  if (option(OPTNOCURSES))
    return;

  if (!progress->inc)
    goto out;

  /* refresh if size > inc */
  if (progress->flags & M_PROGRESS_SIZE &&
      (pos >= progress->pos + (progress->inc << 10)))
    update = 1;
  else if (pos >= progress->pos + progress->inc)
    update = 1;

  /* skip refresh if not enough time has passed */
  if (update && progress->timestamp && !gettimeofday (&tv, NULL)) {
    now = ((unsigned int) tv.tv_sec * 1000)
          + (unsigned int) (tv.tv_usec / 1000);
    if (now && now - progress->timestamp < TimeInc)
      update = 0;
  }

  /* always show the first update */
  if (!pos)
    update = 1;

  if (update)
  {
    if (progress->flags & M_PROGRESS_SIZE)
    {
      pos = pos / (progress->inc << 10) * (progress->inc << 10);
      mutt_pretty_size (posstr, sizeof (posstr), pos);
    }
    else
      snprintf (posstr, sizeof (posstr), "%ld", pos);

    dprint (5, (debugfile, "updating progress: %s\n", posstr));

    progress->pos = pos;
    if (now)
      progress->timestamp = now;

    if (progress->size > 0)
    {
      mutt_message ("%s %s/%s (%d%%)", progress->msg, posstr, progress->sizestr,
		    percent > 0 ? percent :
		   	(int) (100.0 * (double) progress->pos / progress->size));
    }
    else
    {
      if (percent > 0)
	mutt_message ("%s %s (%d%%)", progress->msg, posstr, percent);
      else
	mutt_message ("%s %s", progress->msg, posstr);
    }
  }

out:
  if (pos >= progress->size)
    mutt_clear_error ();
}

void mutt_show_error (void)
{
  if (option (OPTKEEPQUIET))
    return;
  
  SETCOLOR (option (OPTMSGERR) ? MT_COLOR_ERROR : MT_COLOR_MESSAGE);
  mvaddstr(LINES-1, 0, Errorbuf);
  NORMAL_COLOR;
  clrtoeol();
}

void mutt_endwin (const char *msg)
{
  int e = errno;

  if (!option (OPTNOCURSES))
  {
    /* at least in some situations (screen + xterm under SuSE11/12) endwin()
     * doesn't properly flush the screen without an explicit call.
     */
    mutt_refresh();
    endwin ();
  }
  
  if (msg && *msg)
  {
    puts (msg);
    fflush (stdout);
  }

  errno = e;
}

void mutt_perror (const char *s)
{
  char *p = strerror (errno);

