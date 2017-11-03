static void draw_sidebar (int num_rows, int num_cols, int div_width)
{
  int entryidx;
  SBENTRY *entry;
  BUFFY *b;
  if (TopIndex < 0)
    return;

  int w = MIN(num_cols, (SidebarWidth - div_width));
  int row = 0;
  for (entryidx = TopIndex; (entryidx < EntryCount) && (row < num_rows); entryidx++)
  {
    entry = Entries[entryidx];
    if (entry->is_hidden)
      continue;
    b = entry->buffy;

    if (entryidx == OpnIndex)
    {
      if ((ColorDefs[MT_COLOR_SB_INDICATOR] != 0))
        SETCOLOR(MT_COLOR_SB_INDICATOR);
      else
        SETCOLOR(MT_COLOR_INDICATOR);
    }
    else if (entryidx == HilIndex)
      SETCOLOR(MT_COLOR_HIGHLIGHT);
    else if ((ColorDefs[MT_COLOR_SB_SPOOLFILE] != 0) &&
               (mutt_strcmp (b->path, Spoolfile) == 0))
      SETCOLOR(MT_COLOR_SB_SPOOLFILE);
    else if ((b->msg_unread > 0) || (b->new))
      SETCOLOR(MT_COLOR_NEW);
    else if (b->msg_flagged > 0)
      SETCOLOR(MT_COLOR_FLAGGED);
    else
      SETCOLOR(MT_COLOR_NORMAL);

    mutt_window_move (MuttSidebarWindow, row, 0);
    if (Context && Context->realpath &&
        !mutt_strcmp (b->realpath, Context->realpath))
    {
      b->msg_unread  = Context->unread;
      b->msg_count   = Context->msgcount;
      b->msg_flagged = Context->flagged;
    }

    /* compute length of Maildir without trailing separator */
    size_t maildirlen = mutt_strlen (Maildir);
    if (maildirlen &&
        SidebarDelimChars &&
        strchr (SidebarDelimChars, Maildir[maildirlen - 1]))
      maildirlen--;

    /* check whether Maildir is a prefix of the current folder's path */
    short maildir_is_prefix = 0;
    if ((mutt_strlen (b->path) > maildirlen) && (mutt_strncmp (Maildir, b->path, maildirlen) == 0))
      maildir_is_prefix = 1;

    /* calculate depth of current folder and generate its display name with indented spaces */
    int sidebar_folder_depth = 0;
    char *sidebar_folder_name;
    int i;
    if (option (OPTSIDEBARSHORTPATH))
    {
      /* disregard a trailing separator, so strlen() - 2 */
      sidebar_folder_name = b->path;
      for (i = mutt_strlen (sidebar_folder_name) - 2; i >= 0; i--)
      {
        if (SidebarDelimChars &&
            strchr (SidebarDelimChars, sidebar_folder_name[i]))
        {
          sidebar_folder_name += (i + 1);
          break;
        }
      }
    }
    else
      sidebar_folder_name = b->path + maildir_is_prefix * (maildirlen + 1);

    if (maildir_is_prefix && option (OPTSIDEBARFOLDERINDENT))
    {
      const char *tmp_folder_name;
      int lastsep = 0;
      tmp_folder_name = b->path + maildirlen + 1;
      int tmplen = (int) mutt_strlen (tmp_folder_name) - 1;
      for (i = 0; i < tmplen; i++)
      {
        if (SidebarDelimChars && strchr (SidebarDelimChars, tmp_folder_name[i]))
        {
          sidebar_folder_depth++;
          lastsep = i + 1;
        }
      }
      if (sidebar_folder_depth > 0)
      {
        if (option (OPTSIDEBARSHORTPATH))
          tmp_folder_name += lastsep;  /* basename */
        int sfn_len = mutt_strlen (tmp_folder_name) +
                      sidebar_folder_depth*mutt_strlen (SidebarIndentString) + 1;
        sidebar_folder_name = safe_malloc (sfn_len);
        sidebar_folder_name[0]=0;
        for (i=0; i < sidebar_folder_depth; i++)
          safe_strcat (sidebar_folder_name, sfn_len, NONULL(SidebarIndentString));
        safe_strcat (sidebar_folder_name, sfn_len, tmp_folder_name);
      }
    }
    char str[STRING];
    make_sidebar_entry (str, sizeof (str), w, sidebar_folder_name, entry);
    printw ("%s", str);
    if (sidebar_folder_depth > 0)
      FREE (&sidebar_folder_name);
    row++;
  }

  fill_empty_space (row, num_rows - row, w);
}