static int browse_add_list_result (IMAP_DATA* idata, const char* cmd,
  struct browser_state* state, short isparent)
{
  IMAP_LIST list;
  IMAP_MBOX mx;
  int rc;

  if (imap_parse_path (state->folder, &mx))
  {
    dprint (2, (debugfile,
      "browse_add_list_result: current folder %s makes no sense\n", state->folder));
    return -1;
  }

  imap_cmd_start (idata, cmd);
  idata->cmdtype = IMAP_CT_LIST;
  idata->cmddata = &list;
  do
  {
    list.name = NULL;
    rc = imap_cmd_step (idata);

    if (rc == IMAP_CMD_CONTINUE && list.name)
    {
      /* Let a parent folder never be selectable for navigation */
      if (isparent)
        list.noselect = 1;
      /* prune current folder from output */
      if (isparent || mutt_strncmp (list.name, mx.mbox, strlen (list.name)))
        imap_add_folder (list.delim, list.name, list.noselect, list.noinferiors,
                         state, isparent);
    }
  }
  while (rc == IMAP_CMD_CONTINUE);
  idata->cmddata = NULL;

  FREE (&mx.mbox);
  return rc == IMAP_CMD_OK ? 0 : -1;
}