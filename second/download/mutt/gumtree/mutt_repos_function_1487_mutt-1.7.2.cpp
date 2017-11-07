static void mh_update_maildir (struct maildir *md, struct mh_sequences *mhs)
{
  int i;
  short f;
  char *p;

  for (; md; md = md->next)
  {
    if ((p = strrchr (md->h->path, '/')))
      p++;
    else
      p = md->h->path;

    if (mutt_atoi (p, &i) < 0)
      continue;
    f = mhs_check (mhs, i);

    md->h->read = (f & MH_SEQ_UNSEEN) ? 0 : 1;
    md->h->flagged = (f & MH_SEQ_FLAGGED) ? 1 : 0;
    md->h->replied = (f & MH_SEQ_REPLIED) ? 1 : 0;
  }
}