static void unsort_entries (void)
{
  BUFFY *cur = Incoming;
  int i = 0, j;
  SBENTRY *tmp;

  while (cur && (i < EntryCount))
  {
    j = i;
    while ((j < EntryCount) &&
           (Entries[j]->buffy != cur))
      j++;
    if (j < EntryCount)
    {
      if (j != i)
      {
        tmp = Entries[i];
        Entries[i] = Entries[j];
        Entries[j] = tmp;
      }
      i++;
    }
    cur = cur->next;
  }
}