static void mhs_free_sequences (struct mh_sequences *mhs)
{
  FREE (&mhs->flags);
}