void mutt_update_mailbox (BUFFY * b)
{
  struct stat sb;

  if (!b)
    return;

  if (stat (b->path, &sb) == 0)
    b->size = (off_t) sb.st_size;
  else
    b->size = 0;
  return;
}