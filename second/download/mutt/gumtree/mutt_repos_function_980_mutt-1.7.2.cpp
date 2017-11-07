static void attach_forward_msgs (FILE * fp, HEADER * hdr, 
	       ATTACHPTR ** idx, short idxlen, BODY * cur)
{
  HEADER *curhdr = NULL;
  HEADER *tmphdr;
  short i;
  int rc;

  BODY **last;
  char tmpbody[_POSIX_PATH_MAX];
  FILE *tmpfp = NULL;

  int cmflags = 0;
  int chflags = CH_XMIT;
  
  if (cur)
    curhdr = cur->hdr;
  else
  {
    for (i = 0; i < idxlen; i++)
      if (idx[i]->content->tagged)
      {
	curhdr = idx[i]->content->hdr;
	break;
      }
  }

  tmphdr = mutt_new_header ();
  tmphdr->env = mutt_new_envelope ();
  mutt_make_forward_subject (tmphdr->env, Context, curhdr);


  tmpbody[0] = '\0';

  if ((rc = query_quadoption (OPT_MIMEFWD, 
		 _("Forward MIME encapsulated?"))) == MUTT_NO)
  {
    
    /* no MIME encapsulation */
    
    mutt_mktemp (tmpbody, sizeof (tmpbody));
    if (!(tmpfp = safe_fopen (tmpbody, "w")))
    {
      mutt_error (_("Can't create %s."), tmpbody);
      mutt_free_header (&tmphdr);
      return;
    }

    if (option (OPTFORWQUOTE))
    {
      chflags |= CH_PREFIX;
      cmflags |= MUTT_CM_PREFIX;
    }

    if (option (OPTFORWDECODE))
    {
      cmflags |= MUTT_CM_DECODE | MUTT_CM_CHARCONV;
      if (option (OPTWEED))
      {
	chflags |= CH_WEED | CH_REORDER;
	cmflags |= MUTT_CM_WEED;
      }
    }
    
    
    if (cur)
    {
      /* mutt_message_hook (cur->hdr, MUTT_MESSAGEHOOK); */ 
      mutt_forward_intro (tmpfp, cur->hdr);
      _mutt_copy_message (tmpfp, fp, cur->hdr, cur->hdr->content, cmflags, chflags);
      mutt_forward_trailer (tmpfp);
    }
    else
    {
      for (i = 0; i < idxlen; i++)
      {
	if (idx[i]->content->tagged)
	{
	  /* mutt_message_hook (idx[i]->content->hdr, MUTT_MESSAGEHOOK); */ 
	  mutt_forward_intro (tmpfp, idx[i]->content->hdr);
	  _mutt_copy_message (tmpfp, fp, idx[i]->content->hdr,
			      idx[i]->content->hdr->content, cmflags, chflags);
	  mutt_forward_trailer (tmpfp);
	}
      }
    }
    safe_fclose (&tmpfp);
  }
  else if (rc == MUTT_YES)	/* do MIME encapsulation - we don't need to do much here */
  {
    last = &tmphdr->content;
    if (cur)
      mutt_copy_body (fp, last, cur);
    else
    {
      for (i = 0; i < idxlen; i++)
	if (idx[i]->content->tagged)
	{
	  mutt_copy_body (fp, last, idx[i]->content);
	  last = &((*last)->next);
	}
    }
  }
  else
    mutt_free_header (&tmphdr);

  ci_send_message (0, tmphdr, *tmpbody ? tmpbody : NULL, 
		   NULL, curhdr);

}