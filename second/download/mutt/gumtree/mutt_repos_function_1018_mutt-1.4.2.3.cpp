static void maildir_free_entry(struct maildir **md)
{
  if(!md || !*md)
    return;

  safe_free((void **) &(*md)->canon_fname);
  if((*md)->h)
    mutt_free_header(&(*md)->h);

  safe_free((void **) md);
}