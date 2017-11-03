static int select_prev_new (void)
{
  int entry = HilIndex;

  if (!EntryCount || HilIndex < 0)
    return 0;

  do
  {
    entry--;
    if (entry < 0)
    {
      if (option (OPTSIDEBARNEXTNEWWRAP))
        entry = EntryCount - 1;
      else
        return 0;
    }
    if (entry == HilIndex)
      return 0;
  } while (!Entries[entry]->buffy->new &&
           !Entries[entry]->buffy->msg_unread);

  HilIndex = entry;
  return 1;
}