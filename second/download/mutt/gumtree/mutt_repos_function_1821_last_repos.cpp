static void update_entries_visibility (void)
{
  short new_only = option (OPTSIDEBARNEWMAILONLY);
  SBENTRY *sbe;
  int i;

  for (i = 0; i < EntryCount; i++)
  {
    sbe = Entries[i];

    sbe->is_hidden = 0;

    if (!new_only)
      continue;

    if ((i == OpnIndex) || (sbe->buffy->msg_unread  > 0) || sbe->buffy->new ||
        (sbe->buffy->msg_flagged > 0))
      continue;

    if (Context && (mutt_strcmp (sbe->buffy->realpath, Context->realpath) == 0))
      /* Spool directory */
      continue;

    if (mutt_find_list (SidebarWhitelist, sbe->buffy->path))
      /* Explicitly asked to be visible */
      continue;

    sbe->is_hidden = 1;
  }
}