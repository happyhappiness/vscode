void mutt_attach_reply (FILE * fp, HEADER * hdr, 
			ATTACHPTR ** idx, short idxlen, BODY * cur, 
			int flags)
{
  short mime_reply_any = 0;
  
  short nattach = 0;
  HEADER *parent = NULL;
  HEADER *tmphdr = NULL;
  short i;

  STATE st;
  char tmpbody[_POSIX_PATH_MAX];
  FILE *tmpfp;
  
  char prefix[SHORT_STRING];
  int rc;
  
  if (check_all_msg (idx, idxlen, cur, 0) == -1)
  {
    nattach = count_tagged (idx, idxlen);
    if ((parent = find_parent (idx, idxlen, cur, nattach)) == NULL)
      parent = hdr;
  }

  if (nattach > 1 && !check_can_decode (idx, idxlen, cur))
  {
    if ((rc = query_quadoption (OPT_MIMEFWDREST,
      _("Can't decode all tagged attachments.  MIME-encapsulate the others?"))) == -1)
      return;
    else if (rc == MUTT_YES)
      mime_reply_any = 1;
  }
  else if (nattach == 1)
    mime_reply_any = 1;

  tmphdr = mutt_new_header ();
  tmphdr->env = mutt_new_envelope ();

  if (attach_reply_envelope_defaults (tmphdr->env, idx, idxlen, 
				      parent ? parent : (cur ? cur->hdr : NULL), flags) == -1)
  {
    mutt_free_header (&tmphdr);
    return;
  }
  
  mutt_mktemp (tmpbody, sizeof (tmpbody));
  if ((tmpfp = safe_fopen (tmpbody, "w")) == NULL)
  {
    mutt_error (_("Can't create %s."), tmpbody);
    mutt_free_header (&tmphdr);
    return;
  }

  if (!parent)
  {
    if (cur)
      attach_include_reply (fp, tmpfp, cur->hdr, flags);
    else
    {
      for (i = 0; i < idxlen; i++)
      {
	if (idx[i]->content->tagged)
	  attach_include_reply (fp, tmpfp, idx[i]->content->hdr, flags);
      }
    }
  }
  else
  {
    mutt_make_attribution (Context, parent, tmpfp);
    
    memset (&st, 0, sizeof (STATE));
    st.fpin = fp;
    st.fpout = tmpfp;

    if (!option (OPTTEXTFLOWED))
      _mutt_make_string (prefix, sizeof (prefix), NONULL (Prefix), 
			 Context, parent, 0);
    else
      strfcpy (prefix, ">", sizeof (prefix));

    st.prefix = prefix;
    st.flags  = MUTT_CHARCONV;
    
    if (option (OPTWEED)) 
      st.flags |= MUTT_WEED;

    if (option (OPTHEADER))
      include_header (1, fp, parent, tmpfp, prefix);

    if (cur)
    {
      if (mutt_can_decode (cur))
      {
	mutt_body_handler (cur, &st);
	state_putc ('\n', &st);
      }
      else
	mutt_copy_body (fp, &tmphdr->content, cur);
    }
    else
    {
      for (i = 0; i < idxlen; i++)
      {
	if (idx[i]->content->tagged && mutt_can_decode (idx[i]->content))
	{
	  mutt_body_handler (idx[i]->content, &st);
	  state_putc ('\n', &st);
	}
      }
    }

    mutt_make_post_indent (Context, parent, tmpfp);

    if (mime_reply_any && !cur && 
	copy_problematic_attachments (fp, &tmphdr->content, idx, idxlen, 0) == NULL)
    {
      mutt_free_header (&tmphdr);
      safe_fclose (&tmpfp);
      return;
    }
  }

  safe_fclose (&tmpfp);
  
  if (ci_send_message (flags, tmphdr, tmpbody, NULL,
			  parent ? parent : (cur ? cur->hdr : NULL)) == 0)
    mutt_set_flag (Context, hdr, MUTT_REPLIED, 1);
}