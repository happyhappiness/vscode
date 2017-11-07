static void maildir_free_entry (struct maildir **md)
{
  if (!md || !*md)
    return;

  FREE (&(*md)->canon_fname);
  if ((*md)->h)
    mutt_free_header (&(*md)->h);

  FREE (md);		/* __FREE_CHECKED__ */
}