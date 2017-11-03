static void mhs_alloc (struct mh_sequences *mhs, int i)
{
  int j;
  int newmax;

  if (i > mhs->max || !mhs->flags)
  {
    newmax = i + 128;
    j = mhs->flags ? mhs->max + 1 : 0;
    safe_realloc (&mhs->flags, sizeof (mhs->flags[0]) * (newmax + 1));
    while (j <= newmax)
      mhs->flags[j++] = 0;

    mhs->max = newmax;
  }
}