static int select_page_down (void)
{
  int orig_hil_index = HilIndex;

  if (!EntryCount || BotIndex < 0)
    return 0;

  HilIndex = BotIndex;
  select_next ();
  /* If the rest of the entries are hidden, go up to the last unhidden one */
  if (Entries[HilIndex]->is_hidden)
    select_prev ();

  return (orig_hil_index != HilIndex);
}