void mutt_sb_set_open_buffy (void)
{
  int entry;

  OpnIndex = -1;

  if (!Context)
    return;

  for (entry = 0; entry < EntryCount; entry++)
  {
    if (!mutt_strcmp (Entries[entry]->buffy->realpath, Context->realpath))
    {
      OpnIndex = entry;
      HilIndex = entry;
      break;
    }
  }
}