static int select_prev (void)
{
  int entry = HilIndex;

  if (!EntryCount || HilIndex < 0)
    return 0;

  do
  {
    entry--;
    if (entry < 0)
      return 0;
  } while (Entries[entry]->is_hidden);

  HilIndex = entry;
  return 1;
}