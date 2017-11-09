static void sort_entries (void)
{
  short ssm = (SidebarSortMethod & SORT_MASK);

  /* These are the only sort methods we understand */
  if ((ssm == SORT_COUNT)     ||
      (ssm == SORT_UNREAD)    ||
      (ssm == SORT_FLAGGED)   ||
      (ssm == SORT_PATH))
    qsort (Entries, EntryCount, sizeof (*Entries), cb_qsort_sbe);
  else if ((ssm == SORT_ORDER) &&
           (SidebarSortMethod != PreviousSort))
    unsort_entries ();
}