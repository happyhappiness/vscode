void mutt_sb_notify_mailbox (BUFFY *b, int created)
{
  int del_index;

  if (!b)
    return;

  /* Any new/deleted mailboxes will cause a refresh.  As long as
   * they're valid, our pointers will be updated in prepare_sidebar() */

  if (created)
  {
    if (EntryCount >= EntryLen)
    {
      EntryLen += 10;
      safe_realloc (&Entries, EntryLen * sizeof (SBENTRY *));
    }
    Entries[EntryCount] = safe_calloc (1, sizeof(SBENTRY));
    Entries[EntryCount]->buffy = b;

    if (TopIndex < 0)
      TopIndex = EntryCount;
    if (BotIndex < 0)
      BotIndex = EntryCount;
    if ((OpnIndex < 0) && Context &&
        (mutt_strcmp (b->realpath, Context->realpath) == 0))
      OpnIndex = EntryCount;

    EntryCount++;
  }
  else
  {
    for (del_index = 0; del_index < EntryCount; del_index++)
      if (Entries[del_index]->buffy == b)
        break;
    if (del_index == EntryCount)
      return;
    FREE (&Entries[del_index]);
    EntryCount--;

    if (TopIndex > del_index || TopIndex == EntryCount)
      TopIndex--;
    if (OpnIndex == del_index)
      OpnIndex = -1;
    else if (OpnIndex > del_index)
      OpnIndex--;
    if (HilIndex > del_index || HilIndex == EntryCount)
      HilIndex--;
    if (BotIndex > del_index || BotIndex == EntryCount)
      BotIndex--;

    for (; del_index < EntryCount; del_index++)
      Entries[del_index] = Entries[del_index + 1];
  }

  mutt_set_current_menu_redraw (REDRAW_SIDEBAR);
}