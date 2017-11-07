FILE *maildir_open_find_message (const char *folder, const char *msg)
{
  char unique[_POSIX_PATH_MAX];
  FILE *fp;

  static unsigned int new_hits = 0, cur_hits = 0;	/* simple dynamic optimization */

  maildir_canon_filename (unique, msg, sizeof (unique));

  if (
      (fp =
       _maildir_open_find_message (folder, unique,
				   new_hits > cur_hits ? "new" : "cur"))
      || errno != ENOENT)
  {
    if (new_hits < UINT_MAX && cur_hits < UINT_MAX)
    {
      new_hits += (new_hits > cur_hits ? 1 : 0);
      cur_hits += (new_hits > cur_hits ? 0 : 1);
    }

    return fp;
  }
  if (
      (fp =
       _maildir_open_find_message (folder, unique,
				   new_hits > cur_hits ? "cur" : "new"))
      || errno != ENOENT)
  {
    if (new_hits < UINT_MAX && cur_hits < UINT_MAX)
    {
      new_hits += (new_hits > cur_hits ? 0 : 1);
      cur_hits += (new_hits > cur_hits ? 1 : 0);
    }

    return fp;
  }

  return NULL;
}