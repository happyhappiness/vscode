int mutt_num_postponed (int force)
{
  struct stat st;
  CONTEXT ctx;

  static time_t LastModify = 0;
  static char *OldPostponed = NULL;

  if (UpdateNumPostponed)
  {
    UpdateNumPostponed = 0;
    force = 1;
  }

  if (mutt_strcmp (Postponed, OldPostponed))
  {
    FREE (&OldPostponed);
    OldPostponed = safe_strdup (Postponed);
    LastModify = 0;
    force = 1;
  }

  if (!Postponed)
    return 0;

#ifdef USE_IMAP
  /* LastModify is useless for IMAP */
  if (mx_is_imap (Postponed))
  {
    if (force)
    {
      short newpc;

      newpc = imap_status (Postponed, 0);
      if (newpc >= 0)
      {
	PostCount = newpc;
	dprint (3, (debugfile, "mutt_num_postponed: %d postponed IMAP messages found.\n", PostCount));
      }
      else
	dprint (3, (debugfile, "mutt_num_postponed: using old IMAP postponed count.\n"));
    }
    return PostCount;
  }
#endif

  if (stat (Postponed, &st) == -1)
  {
     PostCount = 0;
     LastModify = 0;
     return (0);
  }

  if (S_ISDIR (st.st_mode))
  {
    /* if we have a maildir mailbox, we need to stat the "new" dir */

    char buf[_POSIX_PATH_MAX];

    snprintf (buf, sizeof (buf), "%s/new", Postponed);
    if (access (buf, F_OK) == 0 && stat (buf, &st) == -1)
    {
      PostCount = 0;
      LastModify = 0;
      return 0;
    }
  }

  if (LastModify < st.st_mtime)
  {
    LastModify = st.st_mtime;

    if (access (Postponed, R_OK | F_OK) != 0)
      return (PostCount = 0);
    if (mx_open_mailbox (Postponed, MUTT_NOSORT | MUTT_QUIET, &ctx) == NULL)
      PostCount = 0;
    else
      PostCount = ctx.msgcount;
    mx_fastclose_mailbox (&ctx);
  }

  return (PostCount);
}