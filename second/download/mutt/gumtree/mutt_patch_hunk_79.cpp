 	force_redraw = 0;
 
 	while (lines < bodylen && lineInfo[curline].offset <= sb.st_size - 1)
 	{
 	  if (display_line (fp, &last_pos, &lineInfo, curline, &lastLine, 
 			    &maxLine,
-			    (flags & M_DISPLAYFLAGS) | hideQuoted | SearchFlag, 
+			    (flags & M_DISPLAYFLAGS) | hideQuoted | SearchFlag | (flags & M_PAGER_NOWRAP),
 			    &QuoteList, &q_level, &force_redraw, &SearchRE) > 0)
 	    lines++;
 	  curline++;
 	}
 	last_offset = lineInfo[curline].offset;
       } while (force_redraw);
 
       SETCOLOR (MT_COLOR_TILDE);
-      BKGDSET (MT_COLOR_TILDE);
       while (lines < bodylen)
       {
 	clrtoeol ();
 	if (option (OPTTILDE))
 	  addch ('~');
 	addch ('\n');
 	lines++;
       }
+      NORMAL_COLOR;
+
       /* We are going to update the pager status bar, so it isn't
        * necessary to reset to normal color now. */
 
       redraw |= REDRAW_STATUS; /* need to update the % seen */
     }
 
     if (redraw & REDRAW_STATUS)
     {
+      struct hdr_format_info hfi;
+      char pager_progress_str[4];
+
+      hfi.ctx = Context;
+      hfi.pager_progress = pager_progress_str;
+
+      if (last_pos < sb.st_size - 1)
+	snprintf(pager_progress_str, sizeof(pager_progress_str), OFF_T_FMT "%%", (100 * last_offset / sb.st_size));
+      else
+	strfcpy(pager_progress_str, (topline == 0) ? "all" : "end", sizeof(pager_progress_str));
+
       /* print out the pager status bar */
+      move (statusoffset, 0);
       SETCOLOR (MT_COLOR_STATUS);
-      BKGDSET (MT_COLOR_STATUS);
-      CLEARLINE (statusoffset);
-      if (IsHeader (extra))
-      {
-	_mutt_make_string (buffer,
-			   COLS-9 < sizeof (buffer) ? COLS-9 : sizeof (buffer),
-			   NONULL (PagerFmt), Context, extra->hdr, M_FORMAT_MAKEPRINT);
-      }
-      else if (IsMsgAttach (extra))
-      {
-	_mutt_make_string (buffer,
-			   COLS - 9 < sizeof (buffer) ? COLS - 9: sizeof (buffer),
-			   NONULL (PagerFmt), Context, extra->bdy->hdr, M_FORMAT_MAKEPRINT);
-      }
-      mutt_paddstr (COLS-10, IsHeader (extra) || IsMsgAttach (extra) ?
-		    buffer : banner);
-      addstr (" -- (");
-      if (last_pos < sb.st_size - 1)
-	printw ("%d%%)", (int) (100 * last_offset / sb.st_size));
+
+      if (IsHeader (extra) || IsMsgAttach (extra))
+      {
+	size_t l1 = COLS * MB_LEN_MAX;
+	size_t l2 = sizeof (buffer);
+	hfi.hdr = (IsHeader (extra)) ? extra->hdr : extra->bdy->hdr;
+	mutt_make_string_info (buffer, l1 < l2 ? l1 : l2, NONULL (PagerFmt), &hfi, M_FORMAT_MAKEPRINT);
+	mutt_paddstr (COLS, buffer);
+      }
       else
-	addstr (topline == 0 ? "all)" : "end)");
-      BKGDSET (MT_COLOR_NORMAL);
-      SETCOLOR (MT_COLOR_NORMAL);
+      {
+	char bn[STRING];
+	snprintf (bn, sizeof (bn), "%s (%s)", banner, pager_progress_str);
+	mutt_paddstr (COLS, bn);
+      }
+      NORMAL_COLOR;
     }
 
     if ((redraw & REDRAW_INDEX) && index)
     {
       /* redraw the pager_index indicator, because the
        * flags for this message might have changed. */
