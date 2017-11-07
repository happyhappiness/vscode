static void attach_forward_bodies (FILE * fp, HEADER * hdr,
				   ATTACHPTR ** idx, short idxlen,
				   BODY * cur,
				   short nattach)
{
  short i;
  short mime_fwd_all = 0;
  short mime_fwd_any = 1;
  HEADER *parent = NULL;
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


  parent = find_parent (idx, idxlen, cur, nattach);
  
  if (parent == NULL)
    parent = hdr;


  tmphdr = mutt_new_header ();
  tmphdr->env = mutt_new_envelope ();
  mutt_make_forward_subject (tmphdr->env, Context, parent);

  mutt_mktemp (tmpbody, sizeof (tmpbody));
  if ((tmpfp = safe_fopen (tmpbody, "w")) == NULL)
  {
    mutt_error (_("Can't open temporary file %s."), tmpbody);
    return;
  }

  mutt_forward_intro (tmpfp, parent);

  /* prepare the prefix here since we'll need it later. */

  if (option (OPTFORWQUOTE))
  {
    if (!option (OPTTEXTFLOWED))
      _mutt_make_string (prefix, sizeof (prefix), NONULL (Prefix), Context,
			 parent, 0);
    else
      strfcpy (prefix, ">", sizeof (prefix));
  }
    
  include_header (option (OPTFORWQUOTE), fp, parent,
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
      && !check_can_decode (idx, idxlen, cur))
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
  st.fpin = fp;
  st.fpout = tmpfp;

  /* where do we append new MIME parts? */
  last = &tmphdr->content;

  if (cur)
  {
    /* single body case */

    if (!mime_fwd_all && mutt_can_decode (cur))
    {
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
      for (i = 0; i < idxlen; i++)
      {
	if (idx[i]->content->tagged && mutt_can_decode (idx[i]->content))
	{
	  mutt_body_handler (idx[i]->content, &st);
	  state_putc ('\n', &st);
	}
      }
    }

    if (mime_fwd_any && 
	copy_problematic_attachments (fp, last, idx, idxlen, mime_fwd_all) == NULL)
      goto bail;
  }
  
  mutt_forward_trailer (tmpfp);
  
  safe_fclose (&tmpfp);
  tmpfp = NULL;

  /* now that we have the template, send it. */
  ci_send_message (0, tmphdr, tmpbody, NULL, parent);
  return;
  
  bail:
  
  if (tmpfp)
  {
    safe_fclose (&tmpfp);
    mutt_unlink (tmpbody);
  }

  mutt_free_header (&tmphdr);
}