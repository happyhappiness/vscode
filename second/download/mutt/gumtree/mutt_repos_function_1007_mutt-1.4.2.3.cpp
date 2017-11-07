static void mhs_free_sequences (struct mh_sequences *mhs)
{
  safe_free ((void **) &mhs->flags);
}