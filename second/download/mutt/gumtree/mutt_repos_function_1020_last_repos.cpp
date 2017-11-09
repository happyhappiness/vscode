void mutt_attach_reply (FILE * fp, HEADER * hdr,
			ATTACH_CONTEXT *actx, BODY * cur,
			int flags)
{
  short mime_reply_any = 0;
  
  short nattach = 0;
  ATTACHPTR *parent = NULL;
  HEADER *parent_hdr = NULL;
  FILE *parent_fp = NULL;
  HEADER *tmphdr = NULL;
  short i;

  STATE st;
  char tmpbody[_POSIX_PATH_MAX];
  FILE *tmpfp;
  
  char prefix[SHORT_STRING];
  int rc;
  
  if (check_all_msg (actx, cur, 0) == -1)
  {
    nattach = count_tagged (actx);
    if ((parent = find_parent (actx, cur, nattach)) != NULL)
    {
      parent_hdr = parent->content->hdr;
      parent_fp = parent->fp;
    }
    else
    {
      parent_hdr = hdr;
      parent_fp = actx->root_fp;
    }
  }

  if (nattach > 1 && !check_can_decode (actx, cur))
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

  if (attach_reply_envelope_defaults (tmphdr->env, actx,
				      parent_hdr ? parent_hdr : (cur ? cur->hdr : NULL), flags) == -1)
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

  if (!parent_hdr)
  {
    if (cur)
      attach_include_reply (fp, tmpfp, cur->hdr, flags);
    else
    {
      for (i = 0; i < actx->idxlen; i++)
      {
	if (actx->idx[i]->content->tagged)
	  attach_include_reply (actx->idx[i]->fp, tmpfp, actx->idx[i]->content->hdr, flags);
      }
    }
  }
  else
  {
    mutt_make_attribution (Context, parent_hdr, tmpfp);
    
    memset (&st, 0, sizeof (STATE));
    st.fpout = tmpfp;

    if (!option (OPTTEXTFLOWED))
      _mutt_make_string (prefix, sizeof (prefix), NONULL (Prefix), 
			 Context, parent_hdr, 0);
    else
      strfcpy (prefix, ">", sizeof (prefix));

    st.prefix = prefix;
    st.flags  = MUTT_CHARCONV;
    
    if (option (OPTWEED)) 
      st.flags |= MUTT_WEED;

    if (option (OPTHEADER))
      include_header (1, parent_fp, parent_hdr, tmpfp, prefix);

    if (cur)
    {
      if (mutt_can_decode (cur))
      {
        st.fpin = fp;
	mutt_body_handler (cur, &st);
	state_putc ('\n', &st);
      }
      else
	mutt_copy_body (fp, &tmphdr->content, cur);
    }
    else
    {
      for (i = 0; i < actx->idxlen; i++)
      {
	if (actx->idx[i]->content->tagged && mutt_can_decode (actx->idx[i]->content))
	{
          st.fpin = actx->idx[i]->fp;
	  mutt_body_handler (actx->idx[i]->content, &st);
	  state_putc ('\n', &st);
	}
      }
    }

    mutt_make_post_indent (Context, parent_hdr, tmpfp);

    if (mime_reply_any && !cur && 
	copy_problematic_attachments (&tmphdr->content, actx, 0) == NULL)
    {
      mutt_free_header (&tmphdr);
      safe_fclose (&tmpfp);
      return;
    }
  }

  safe_fclose (&tmpfp);
  
  if (ci_send_message (flags, tmphdr, tmpbody, NULL,
			  parent_hdr ? parent_hdr : (cur ? cur->hdr : NULL)) == 0)
    mutt_set_flag (Context, hdr, MUTT_REPLIED, 1);
}