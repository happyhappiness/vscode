void mutt_buffy_cleanup (const char *buf, struct stat *st)
{
  struct utimbuf ut;
  BUFFY *tmp;

  if (option(OPTCHECKMBOXSIZE))
  {
    tmp = mutt_find_mailbox (buf);
    if (tmp && !tmp->new)
      mutt_update_mailbox (tmp);
  }
  else
  {
    /* fix up the times so buffy won't get confused */
    if (st->st_mtime > st->st_atime)
    {
      ut.actime = st->st_atime;
      ut.modtime = time (NULL);
      utime (buf, &ut); 
    }
    else
      utime (buf, NULL);
  }
}