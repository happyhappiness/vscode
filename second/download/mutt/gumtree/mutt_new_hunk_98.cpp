      if (!option (OPTATTACHSPLIT))
      {
	if (!buf[0])
	{
	  int append = 0;

	  strfcpy (buf, mutt_basename (NONULL (top->filename)), sizeof (buf));
	  prepend_curdir (buf, sizeof (buf));

	  if (mutt_get_field (_("Save to file: "), buf, sizeof (buf),
				    M_FILE | M_CLEAR) != 0 || !buf[0])
	    return;
	  mutt_expand_path (buf, sizeof (buf));
	  if (mutt_check_overwrite (top->filename, buf, tfile,
				    sizeof (tfile), &append, NULL))
	    return;
	  rc = mutt_save_attachment (fp, top, tfile, append, hdr);
	  if (rc == 0 && AttachSep && (fpout = fopen (tfile,"a")) != NULL)
	  {
	    fprintf(fpout, "%s", AttachSep);
	    safe_fclose (&fpout);
	  }
	}
	else
	{
	  rc = mutt_save_attachment (fp, top, tfile, M_SAVE_APPEND, hdr);
	  if (rc == 0 && AttachSep && (fpout = fopen (tfile,"a")) != NULL)
	  {
	    fprintf(fpout, "%s", AttachSep);
	    safe_fclose (&fpout);
	  }
	}
      }
      else 
      {
	if (tag && menu && top->aptr)
	{
	  menu->oldcurrent = menu->current;
	  menu->current = top->aptr->num;
	  menu_check_recenter (menu);
	  menu->redraw |= REDRAW_MOTION;

	  menu_redraw (menu);
	}
	if (mutt_query_save_attachment (fp, top, hdr, &directory) == -1)
	  break;
      }
    }
    else if (top->parts)
      mutt_save_attachment_list (fp, 1, top->parts, hdr, menu);
    if (!tag)
      break;
  }

  FREE (&directory);

  if (tag && menu)
  {
    menu->oldcurrent = menu->current;
    menu->current = last;
    menu_check_recenter (menu);
    menu->redraw |= REDRAW_MOTION;
  }
  
  if (!option (OPTATTACHSPLIT) && (rc == 0))
    mutt_message _("Attachment saved.");
}

static void
mutt_query_pipe_attachment (char *command, FILE *fp, BODY *body, int filter)
