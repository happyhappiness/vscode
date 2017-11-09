void mutt_save_attachment_list (ATTACH_CONTEXT *actx, FILE *fp, int tag, BODY *top, HEADER *hdr, MUTTMENU *menu)
{
  char buf[_POSIX_PATH_MAX], tfile[_POSIX_PATH_MAX];
  char *directory = NULL;
  int i, rc = 1;
  int last = menu ? menu->current : -1;
  FILE *fpout;

  buf[0] = 0;

  for (i = 0; !tag || i < actx->idxlen; i++)
  {
    if (tag)
    {
      fp = actx->idx[i]->fp;
      top = actx->idx[i]->content;
    }
    if (!tag || top->tagged)
    {
      if (!option (OPTATTACHSPLIT))
      {
	if (!buf[0])
	{
	  int append = 0;

	  strfcpy (buf, mutt_basename (NONULL (top->filename)), sizeof (buf));
	  prepend_curdir (buf, sizeof (buf));

	  if (mutt_get_field (_("Save to file: "), buf, sizeof (buf),
				    MUTT_FILE | MUTT_CLEAR) != 0 || !buf[0])
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
	  rc = mutt_save_attachment (fp, top, tfile, MUTT_SAVE_APPEND, hdr);
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