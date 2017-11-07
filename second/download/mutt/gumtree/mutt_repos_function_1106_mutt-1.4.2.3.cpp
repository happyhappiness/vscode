int mutt_save_attachment (FILE *fp, BODY *m, char *path, int flags, HEADER *hdr)
{
  if (fp)
  {
    
    /* recv mode */

    if(hdr &&
	m->hdr &&
	m->encoding != ENCBASE64 &&
	m->encoding != ENCQUOTEDPRINTABLE &&
	mutt_is_message_type(m->type, m->subtype))
    {
      /* message type attachments are written to mail folders. */

      char buf[HUGE_STRING];
      HEADER *hn;
      CONTEXT ctx;
      MESSAGE *msg;
      int chflags = 0;
      int r = -1;
      
      hn = m->hdr;
      hn->msgno = hdr->msgno; /* required for MH/maildir */
      hn->read = 1;

      fseek (fp, m->offset, 0);
      if (fgets (buf, sizeof (buf), fp) == NULL)
	return -1;
      if (mx_open_mailbox(path, M_APPEND | M_QUIET, &ctx) == NULL)
	return -1;
      if ((msg = mx_open_new_message (&ctx, hn, is_from (buf, NULL, 0, NULL) ? 0 : M_ADD_FROM)) == NULL)
      {
	mx_close_mailbox(&ctx, NULL);
	return -1;
      }
      if (ctx.magic == M_MBOX || ctx.magic == M_MMDF || ctx.magic == M_KENDRA)
	chflags = CH_FROM;
      chflags |= (ctx.magic == M_MAILDIR ? CH_NOSTATUS : CH_UPDATE);
      if (_mutt_copy_message (msg->fp, fp, hn, hn->content, 0, chflags) == 0 
	  && mx_commit_message (msg, &ctx) == 0)
	mutt_message _("Attachment saved.");
      else
	r = -1;

      mx_close_message (&msg);
      mx_close_mailbox (&ctx, NULL);
      return r;
    }
    else
    {
      /* In recv mode, extract from folder and decode */
      
      STATE s;
      
      memset (&s, 0, sizeof (s));
      if ((s.fpout = mutt_save_attachment_open (path, flags)) == NULL)
      {
	mutt_perror ("fopen");
	return (-1);
      }
      fseek ((s.fpin = fp), m->offset, 0);
      mutt_decode_attachment (m, &s);
      
      if (fclose (s.fpout) != 0)
      {
	mutt_perror ("fclose");
	return (-1);
      }
    }
  }
  else
  {
    /* In send mode, just copy file */

    FILE *ofp, *nfp;

    if ((ofp = fopen (m->filename, "r")) == NULL)
    {
      mutt_perror ("fopen");
      return (-1);
    }
    
    if ((nfp = mutt_save_attachment_open (path, flags)) == NULL)
    {
      mutt_perror ("fopen");
      safe_fclose (&ofp);
      return (-1);
    }

    if (mutt_copy_stream (ofp, nfp) == -1)
    {
      mutt_error _("Write fault!");
      safe_fclose (&ofp);
      safe_fclose (&nfp);
      return (-1);
    }
    safe_fclose (&ofp);
    safe_fclose (&nfp);
  }

  return 0;
}