static void mhs_alloc (struct mh_sequences *mhs, int i)
{
  int j;
  int newmax;
  
  if (i > mhs->max || !mhs->flags)
  {
    newmax = i + 128;
    safe_realloc ((void **) &mhs->flags, sizeof (mhs->flags[0]) * (newmax + 1));
    for (j = mhs->max + 1; j <= newmax; j++)
      mhs->flags[j] = 0;
    
    mhs->max = newmax;
  }
}