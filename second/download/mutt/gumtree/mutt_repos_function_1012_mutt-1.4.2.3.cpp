int mh_buffy (const char *path)
{
  int i, r = 0;
  struct mh_sequences mhs;
  memset (&mhs, 0, sizeof (mhs));
  
  mh_read_sequences (&mhs, path);
  for (i = 0; !r && i <= mhs.max; i++)
    if (mhs_check (&mhs, i) & MH_SEQ_UNSEEN)
      r = 1;
  mhs_free_sequences (&mhs);
  return r;
}