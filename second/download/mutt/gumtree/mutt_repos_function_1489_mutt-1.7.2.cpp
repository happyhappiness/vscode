static void maildir_free_maildir (struct maildir **md)
{
  struct maildir *p, *q;

  if (!md || !*md)
    return;

  for (p = *md; p; p = q)
  {
    q = p->next;
    maildir_free_entry (&p);
  }
}