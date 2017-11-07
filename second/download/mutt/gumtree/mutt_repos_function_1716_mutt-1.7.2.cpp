static int prepare_sidebar (int page_size)
{
  int i;
  SBENTRY *opn_entry = NULL, *hil_entry = NULL;
  int page_entries;

  if (!EntryCount || (page_size <= 0))
    return 0;

  if (OpnIndex >= 0)
    opn_entry = Entries[OpnIndex];
  if (HilIndex >= 0)
    hil_entry = Entries[HilIndex];

  update_entries_visibility ();
  sort_entries ();

  for (i = 0; i < EntryCount; i++)
  {
    if (opn_entry == Entries[i])
      OpnIndex = i;
    if (hil_entry == Entries[i])
      HilIndex = i;
  }

  if ((HilIndex < 0) || Entries[HilIndex]->is_hidden ||
      (SidebarSortMethod != PreviousSort))
  {
    if (OpnIndex >= 0)
      HilIndex = OpnIndex;
    else
    {
      HilIndex = 0;
      if (Entries[HilIndex]->is_hidden)
        select_next ();
    }
  }

  /* Set the Top and Bottom to frame the HilIndex in groups of page_size */

  /* If OPTSIDEBARNEMAILONLY is set, some entries may be hidden so we
   * need to scan for the framing interval */
  if (option (OPTSIDEBARNEWMAILONLY))
  {
    TopIndex = BotIndex = -1;
    while (BotIndex < HilIndex)
    {
      TopIndex = BotIndex + 1;
      page_entries = 0;
      while (page_entries < page_size)
      {
        BotIndex++;
        if (BotIndex >= EntryCount)
          break;
        if (! Entries[BotIndex]->is_hidden)
          page_entries++;
      }
    }
  }
  /* Otherwise we can just calculate the interval */
  else
  {
    TopIndex = (HilIndex / page_size) * page_size;
    BotIndex = TopIndex + page_size - 1;
  }

  if (BotIndex > (EntryCount - 1))
    BotIndex = EntryCount - 1;

  PreviousSort = SidebarSortMethod;
  return 1;
}