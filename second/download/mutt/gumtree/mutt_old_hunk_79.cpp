	force_redraw = 0;

	while (lines < bodylen && lineInfo[curline].offset <= sb.st_size - 1)
	{
	  if (display_line (fp, &last_pos, &lineInfo, curline, &lastLine, 
			    &maxLine,
			    (flags & M_DISPLAYFLAGS) | hideQuoted | SearchFlag, 
			    &QuoteList, &q_level, &force_redraw, &SearchRE) > 0)
	    lines++;
	  curline++;
	}
	last_offset = lineInfo[curline].offset;
      } while (force_redraw);

      SETCOLOR (MT_COLOR_TILDE);
      BKGDSET (MT_COLOR_TILDE);
      while (lines < bodylen)
      {
	clrtoeol ();
	if (option (OPTTILDE))
	  addch ('~');
	addch ('\n');
	lines++;
      }
      /* We are going to update the pager status bar, so it isn't
       * necessary to reset to normal color now. */

      redraw |= REDRAW_STATUS; /* need to update the % seen */
    }

    if (redraw & REDRAW_STATUS)
    {
      /* print out the pager status bar */
      SETCOLOR (MT_COLOR_STATUS);
      BKGDSET (MT_COLOR_STATUS);
      CLEARLINE (statusoffset);
      if (IsHeader (extra))
      {
	_mutt_make_string (buffer,
			   COLS-9 < sizeof (buffer) ? COLS-9 : sizeof (buffer),
			   NONULL (PagerFmt), Context, extra->hdr, M_FORMAT_MAKEPRINT);
      }
      else if (IsMsgAttach (extra))
      {
	_mutt_make_string (buffer,
			   COLS - 9 < sizeof (buffer) ? COLS - 9: sizeof (buffer),
			   NONULL (PagerFmt), Context, extra->bdy->hdr, M_FORMAT_MAKEPRINT);
      }
      mutt_paddstr (COLS-10, IsHeader (extra) || IsMsgAttach (extra) ?
		    buffer : banner);
      addstr (" -- (");
      if (last_pos < sb.st_size - 1)
	printw ("%d%%)", (int) (100 * last_offset / sb.st_size));
      else
	addstr (topline == 0 ? "all)" : "end)");
      BKGDSET (MT_COLOR_NORMAL);
      SETCOLOR (MT_COLOR_NORMAL);
    }

    if ((redraw & REDRAW_INDEX) && index)
    {
      /* redraw the pager_index indicator, because the
       * flags for this message might have changed. */
