static short mhs_check (struct mh_sequences *mhs, int i)
{
  if (!mhs->flags || i > mhs->max)
    return 0;
  else
    return mhs->flags[i];
}