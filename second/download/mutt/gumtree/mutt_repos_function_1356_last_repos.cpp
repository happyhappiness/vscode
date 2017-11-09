static void print_attachment_list (ATTACH_CONTEXT *actx, FILE *fp, int tag, BODY *top, STATE *state)
{
  int i;
  char type [STRING];

  for (i = 0; !tag || i < actx->idxlen; i++)
  {
    if (tag)
    {
      fp = actx->idx[i]->fp;
      top = actx->idx[i]->content;
    }
    if (!tag || top->tagged)
    {
      snprintf (type, sizeof (type), "%s/%s", TYPE (top), top->subtype);
      if (!option (OPTATTACHSPLIT) && !rfc1524_mailcap_lookup (top, type, NULL, MUTT_PRINT))
      {
	if (!ascii_strcasecmp ("text/plain", top->subtype) ||
	    !ascii_strcasecmp ("application/postscript", top->subtype))
	  pipe_attachment (fp, top, state);
	else if (mutt_can_decode (top))
	{
	  /* decode and print */

	  char newfile[_POSIX_PATH_MAX] = "";
	  FILE *ifp;

	  mutt_mktemp (newfile, sizeof (newfile));
	  if (mutt_decode_save_attachment (fp, top, newfile, MUTT_PRINTING, 0) == 0)
	  {
	    if ((ifp = fopen (newfile, "r")) != NULL)
	    {
	      mutt_copy_stream (ifp, state->fpout);
	      safe_fclose (&ifp);
	      if (AttachSep)
		state_puts (AttachSep, state);
	    }
	  }
	  mutt_unlink (newfile);
	}
      }
      else
	mutt_print_attachment (fp, top);
    }
    if (!tag)
      break;
  }
}