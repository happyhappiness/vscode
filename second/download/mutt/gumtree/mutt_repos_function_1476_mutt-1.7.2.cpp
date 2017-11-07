static short mhs_set (struct mh_sequences *mhs, int i, short f)
{
  mhs_alloc (mhs, i);
  mhs->flags[i] |= f;
  return mhs->flags[i];
}