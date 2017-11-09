static int select_page_up (void)
{
  int orig_hil_index = HilIndex;

  if (!EntryCount || TopIndex < 0)
    return 0;

  HilIndex = TopIndex;
  select_prev ();
  /* If the rest of the entries are hidden, go down to the last unhidden one */
  if (Entries[HilIndex]->is_hidden)
    select_next ();

  return (orig_hil_index != HilIndex);
}