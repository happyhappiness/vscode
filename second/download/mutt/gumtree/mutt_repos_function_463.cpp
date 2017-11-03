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
    if (progress->flags & MUTT_PROGRESS_SIZE)
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