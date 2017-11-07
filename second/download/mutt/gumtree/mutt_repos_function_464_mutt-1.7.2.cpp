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
  if (progress->flags & MUTT_PROGRESS_SIZE &&
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
    if (progress->flags & MUTT_PROGRESS_SIZE)
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