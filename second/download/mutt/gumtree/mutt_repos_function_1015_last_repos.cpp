static void attach_forward_bodies (FILE * fp, HEADER * hdr,
				   ATTACH_CONTEXT *actx,
				   BODY * cur,
				   short nattach)
{
  short i;
  short mime_fwd_all = 0;
  short mime_fwd_any = 1;
  ATTACHPTR *parent = NULL;
  HEADER *parent_hdr;
  FILE *parent_fp;
  HEADER *tmphdr = NULL;
  BODY **last;
  char tmpbody[_POSIX_PATH_MAX];
  FILE *tmpfp = NULL;

  char prefix[STRING];

  int rc = 0;

  STATE st;

  /* 
   * First, find the parent message.
   * Note: This could be made an option by just
   * putting the following lines into an if block.
   */


  parent = find_parent (actx, cur, nattach);
  if (parent)
  {
    parent_hdr = parent->content->hdr;
    parent_fp = parent->fp;
  }
  else
  {
    parent_hdr = hdr;
    parent_fp = actx->root_fp;
  }


  tmphdr = mutt_new_header ();
  tmphdr->env = mutt_new_envelope ();
  mutt_make_forward_subject (tmphdr->env, Context, parent_hdr);

  mutt_mktemp (tmpbody, sizeof (tmpbody));
  if ((tmpfp = safe_fopen (tmpbody, "w")) == NULL)
  {
    mutt_error (_("Can't open temporary file %s."), tmpbody);
    return;
  }

  mutt_forward_intro (Context, parent_hdr, tmpfp);

  /* prepare the prefix here since we'll need it later. */

  if (option (OPTFORWQUOTE))
  {
    if (!option (OPTTEXTFLOWED))
      _mutt_make_string (prefix, sizeof (prefix), NONULL (Prefix), Context,
			 parent_hdr, 0);
    else
      strfcpy (prefix, ">", sizeof (prefix));
  }
    
  include_header (option (OPTFORWQUOTE), parent_fp, parent_hdr,
		  tmpfp, prefix);


  /* 
   * Now, we have prepared the first part of the message body: The
   * original message's header. 
   *
   * The next part is more interesting: either include the message bodies,
   * or attach them.
   */

  if ((!cur || mutt_can_decode (cur)) &&
      (rc = query_quadoption (OPT_MIMEFWD, 
			      _("Forward as attachments?"))) == MUTT_YES)
    mime_fwd_all = 1;
  else if (rc == -1)
    goto bail;

  /* 
   * shortcut MIMEFWDREST when there is only one attachment.  Is 
   * this intuitive?
   */

  if (!mime_fwd_all && !cur && (nattach > 1) 
      && !check_can_decode (actx, cur))
  {
    if ((rc = query_quadoption (OPT_MIMEFWDREST,
_("Can't decode all tagged attachments.  MIME-forward the others?"))) == -1)
      goto bail;
    else if (rc == MUTT_NO)
      mime_fwd_any = 0;
  }

  /* initialize a state structure */
  
  memset (&st, 0, sizeof (st));
  
  if (option (OPTFORWQUOTE))
    st.prefix = prefix;
  st.flags = MUTT_CHARCONV;
  if (option (OPTWEED))
    st.flags |= MUTT_WEED;
  st.fpout = tmpfp;

  /* where do we append new MIME parts? */
  last = &tmphdr->content;

  if (cur)
  {
    /* single body case */

    if (!mime_fwd_all && mutt_can_decode (cur))
    {
      st.fpin = fp;
      mutt_body_handler (cur, &st);
      state_putc ('\n', &st);
    }
    else
    {
      if (mutt_copy_body (fp, last, cur) == -1)
	goto bail;
      last = &((*last)->next);
    }
  }
  else
  {
    /* multiple body case */

    if (!mime_fwd_all)
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

    if (mime_fwd_any && 
	copy_problematic_attachments (last, actx, mime_fwd_all) == NULL)
      goto bail;
  }
  
  mutt_forward_trailer (Context, parent_hdr, tmpfp);
  
  safe_fclose (&tmpfp);
  tmpfp = NULL;

  /* now that we have the template, send it. */
  ci_send_message (0, tmphdr, tmpbody, NULL, parent_hdr);
  return;
  
  bail:
  
  if (tmpfp)
  {
    safe_fclose (&tmpfp);
    mutt_unlink (tmpbody);
  }

  mutt_free_header (&tmphdr);
}