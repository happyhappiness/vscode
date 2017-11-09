static void pager_menu_redraw (MUTTMENU *pager_menu)
{
  pager_redraw_data_t *rd = pager_menu->redraw_data;
  int i, j, err;
  char buffer[LONG_STRING];

  if (!rd)
    return;

  if (pager_menu->redraw & REDRAW_FULL)
  {
#if ! (defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM))
    mutt_reflow_windows ();
#endif
    NORMAL_COLOR;
    /* clear() doesn't optimize screen redraws */
    move (0, 0);
    clrtobot ();

    if (IsHeader (rd->extra) && Context->vcount + 1 < PagerIndexLines)
      rd->indexlen = Context->vcount + 1;
    else
      rd->indexlen = PagerIndexLines;

    rd->indicator = rd->indexlen / 3;

    memcpy (rd->pager_window, MuttIndexWindow, sizeof(mutt_window_t));
    memcpy (rd->pager_status_window, MuttStatusWindow, sizeof(mutt_window_t));
    rd->index_status_window->rows = rd->index_window->rows = 0;

    if (IsHeader (rd->extra) && PagerIndexLines)
    {
      memcpy (rd->index_window, MuttIndexWindow, sizeof(mutt_window_t));
      rd->index_window->rows = rd->indexlen > 0 ? rd->indexlen - 1 : 0;

      if (option (OPTSTATUSONTOP))
      {
        memcpy (rd->index_status_window, MuttStatusWindow, sizeof(mutt_window_t));

        memcpy (rd->pager_status_window, MuttIndexWindow, sizeof(mutt_window_t));
        rd->pager_status_window->rows = 1;
        rd->pager_status_window->row_offset += rd->index_window->rows;

        rd->pager_window->rows -= rd->index_window->rows + rd->pager_status_window->rows;
        rd->pager_window->row_offset += rd->index_window->rows + rd->pager_status_window->rows;
      }
      else
      {
        memcpy (rd->index_status_window, MuttIndexWindow, sizeof(mutt_window_t));
        rd->index_status_window->rows = 1;
        rd->index_status_window->row_offset += rd->index_window->rows;

        rd->pager_window->rows -= rd->index_window->rows + rd->index_status_window->rows;
        rd->pager_window->row_offset += rd->index_window->rows + rd->index_status_window->rows;
      }
    }

    if (option (OPTHELP))
    {
      SETCOLOR (MT_COLOR_STATUS);
      mutt_window_move (MuttHelpWindow, 0, 0);
      mutt_paddstr (MuttHelpWindow->cols, rd->helpstr);
      NORMAL_COLOR;
    }

#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
    if (Resize != NULL)
    {
      if ((rd->SearchCompiled = Resize->SearchCompiled))
      {
        if ((err = REGCOMP (&rd->SearchRE, rd->searchbuf,
                            REG_NEWLINE | mutt_which_case (rd->searchbuf))) != 0)
        {
          regerror (err, &rd->SearchRE, buffer, sizeof (buffer));
          mutt_error ("%s", buffer);
          rd->SearchCompiled = 0;
        }
        else
        {
          rd->SearchFlag = MUTT_SEARCH;
          rd->SearchBack = Resize->SearchBack;
        }
      }
      rd->lines = Resize->line;
      pager_menu->redraw |= REDRAW_FLOW;

      FREE (&Resize);
    }
#endif

    if (IsHeader (rd->extra) && PagerIndexLines)
    {
      if (rd->index == NULL)
      {
        /* only allocate the space if/when we need the index.
           Initialise the menu as per the main index */
        rd->index = mutt_new_menu(MENU_MAIN);
        rd->index->make_entry = index_make_entry;
        rd->index->color = index_color;
        rd->index->max = Context->vcount;
        rd->index->current = rd->extra->hdr->virtual;
        rd->index->indexwin = rd->index_window;
        rd->index->statuswin = rd->index_status_window;
      }

      NORMAL_COLOR;
      rd->index->pagelen = rd->index_window->rows;;

      /* some fudge to work out where abouts the indicator should go */
      if (rd->index->current - rd->indicator < 0)
        rd->index->top = 0;
      else if (rd->index->max - rd->index->current < rd->index->pagelen - rd->indicator)
        rd->index->top = rd->index->max - rd->index->pagelen;
      else
        rd->index->top = rd->index->current - rd->indicator;

      menu_redraw_index(rd->index);
    }

    pager_menu->redraw |= REDRAW_BODY | REDRAW_INDEX | REDRAW_STATUS;
#ifdef USE_SIDEBAR
    pager_menu->redraw |= REDRAW_SIDEBAR;
#endif
    mutt_show_error ();
  }

  if (pager_menu->redraw & REDRAW_FLOW)
  {
    if (!(rd->flags & MUTT_PAGER_RETWINCH))
    {
      rd->lines = -1;
      for (i = 0; i <= rd->topline; i++)
        if (!rd->lineInfo[i].continuation)
          rd->lines++;
      for (i = 0; i < rd->maxLine; i++)
      {
        rd->lineInfo[i].offset = 0;
        rd->lineInfo[i].type = -1;
        rd->lineInfo[i].continuation = 0;
        rd->lineInfo[i].chunks = 0;
        rd->lineInfo[i].search_cnt = -1;
        rd->lineInfo[i].quote = NULL;

        safe_realloc (&(rd->lineInfo[i].syntax),
                      sizeof (struct syntax_t));
        if (rd->SearchCompiled && rd->lineInfo[i].search)
          FREE (&(rd->lineInfo[i].search));
      }

      rd->lastLine = 0;
      rd->topline = 0;
    }
    i = -1;
    j = -1;
    while (display_line (rd->fp, &rd->last_pos, &rd->lineInfo, ++i, &rd->lastLine, &rd->maxLine,
                         rd->has_types | rd->SearchFlag | (rd->flags & MUTT_PAGER_NOWRAP),
                         &rd->QuoteList, &rd->q_level, &rd->force_redraw,
                         &rd->SearchRE, rd->pager_window) == 0)
      if (!rd->lineInfo[i].continuation && ++j == rd->lines)
      {
        rd->topline = i;
        if (!rd->SearchFlag)
          break;
      }
  }

#ifdef USE_SIDEBAR
  if (pager_menu->redraw & REDRAW_SIDEBAR)
  {
    menu_redraw_sidebar (pager_menu);
  }
#endif

  if ((pager_menu->redraw & REDRAW_BODY) || rd->topline != rd->oldtopline)
  {
    do
    {
      mutt_window_move (rd->pager_window, 0, 0);
      rd->curline = rd->oldtopline = rd->topline;
      rd->lines = 0;
      rd->force_redraw = 0;

      while (rd->lines < rd->pager_window->rows &&
             rd->lineInfo[rd->curline].offset <= rd->sb.st_size - 1)
      {
        if (display_line (rd->fp, &rd->last_pos, &rd->lineInfo, rd->curline, &rd->lastLine, 
                          &rd->maxLine,
                          (rd->flags & MUTT_DISPLAYFLAGS) | rd->hideQuoted | rd->SearchFlag | (rd->flags & MUTT_PAGER_NOWRAP),
                          &rd->QuoteList, &rd->q_level, &rd->force_redraw, &rd->SearchRE,
                          rd->pager_window) > 0)
          rd->lines++;
        rd->curline++;
        mutt_window_move (rd->pager_window, rd->lines, 0);
      }
      rd->last_offset = rd->lineInfo[rd->curline].offset;
    } while (rd->force_redraw);

    SETCOLOR (MT_COLOR_TILDE);
    while (rd->lines < rd->pager_window->rows)
    {
      mutt_window_clrtoeol (rd->pager_window);
      if (option (OPTTILDE))
        addch ('~');
      rd->lines++;
      mutt_window_move (rd->pager_window, rd->lines, 0);
    }
    NORMAL_COLOR;

    /* We are going to update the pager status bar, so it isn't
     * necessary to reset to normal color now. */

    pager_menu->redraw |= REDRAW_STATUS; /* need to update the % seen */
  }

  if (pager_menu->redraw & REDRAW_STATUS)
  {
    struct hdr_format_info hfi;
    char pager_progress_str[4];

    hfi.ctx = Context;
    hfi.pager_progress = pager_progress_str;

    if (rd->last_pos < rd->sb.st_size - 1)
      snprintf(pager_progress_str, sizeof(pager_progress_str), OFF_T_FMT "%%", (100 * rd->last_offset / rd->sb.st_size));
    else
      strfcpy(pager_progress_str, (rd->topline == 0) ? "all" : "end", sizeof(pager_progress_str));

    /* print out the pager status bar */
    mutt_window_move (rd->pager_status_window, 0, 0);
    SETCOLOR (MT_COLOR_STATUS);

    if (IsHeader (rd->extra) || IsMsgAttach (rd->extra))
    {
      size_t l1 = rd->pager_status_window->cols * MB_LEN_MAX;
      size_t l2 = sizeof (buffer);
      hfi.hdr = (IsHeader (rd->extra)) ? rd->extra->hdr : rd->extra->bdy->hdr;
      mutt_make_string_info (buffer, l1 < l2 ? l1 : l2, rd->pager_status_window->cols, NONULL (PagerFmt), &hfi, MUTT_FORMAT_MAKEPRINT);
      mutt_paddstr (rd->pager_status_window->cols, buffer);
    }
    else
    {
      char bn[STRING];
      snprintf (bn, sizeof (bn), "%s (%s)", rd->banner, pager_progress_str);
      mutt_paddstr (rd->pager_status_window->cols, bn);
    }
    NORMAL_COLOR;
    if (option(OPTTSENABLED) && TSSupported)
    {
      menu_status_line (buffer, sizeof (buffer), rd->index, NONULL (TSStatusFormat));
      mutt_ts_status(buffer);
      menu_status_line (buffer, sizeof (buffer), rd->index, NONULL (TSIconFormat));
      mutt_ts_icon(buffer);
    }
  }

  if ((pager_menu->redraw & REDRAW_INDEX) && rd->index)
  {
    /* redraw the pager_index indicator, because the
     * flags for this message might have changed. */
    if (rd->index_window->rows > 0)
      menu_redraw_current (rd->index);

    /* print out the index status bar */
    menu_status_line (buffer, sizeof (buffer), rd->index, NONULL(Status));

    mutt_window_move (rd->index_status_window, 0, 0);
    SETCOLOR (MT_COLOR_STATUS);
    mutt_paddstr (rd->index_status_window->cols, buffer);
    NORMAL_COLOR;
  }

  pager_menu->redraw = 0;
}