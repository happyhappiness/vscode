static int
attach_reply_envelope_defaults (ENVELOPE *env, ATTACH_CONTEXT *actx,
				HEADER *parent, int flags)
{
  ENVELOPE *curenv = NULL;
  HEADER *curhdr = NULL;
  short i;
  
  if (!parent)
  {
    for (i = 0; i < actx->idxlen; i++)
    {
      if (actx->idx[i]->content->tagged)
      {
	curhdr = actx->idx[i]->content->hdr;
	curenv = curhdr->env;
	break;
      }
    }
  }
  else
  {
    curenv = parent->env;
    curhdr = parent;
  }

  if (curenv == NULL  ||  curhdr == NULL)
  {
    mutt_error _("Can't find any tagged messages.");
    return -1;
  }

  if (parent)
  {
    if (mutt_fetch_recips (env, curenv, flags) == -1)
      return -1;
  }
  else
  {
    for (i = 0; i < actx->idxlen; i++)
    {
      if (actx->idx[i]->content->tagged
	  && mutt_fetch_recips (env, actx->idx[i]->content->hdr->env, flags) == -1)
	return -1;
    }
  }
  
  if ((flags & SENDLISTREPLY) && !env->to)
  {
    mutt_error _("No mailing lists found!");
    return (-1);
  }
  
  mutt_fix_reply_recipients (env);
  mutt_make_misc_reply_headers (env, Context, curhdr, curenv);

  if (parent)
    mutt_add_to_reference_headers (env, curenv, NULL, NULL);
  else
  {
    LIST **p = NULL, **q = NULL;
    
    for (i = 0; i < actx->idxlen; i++)
    {
      if (actx->idx[i]->content->tagged)
	mutt_add_to_reference_headers (env, actx->idx[i]->content->hdr->env, &p, &q);
    }
  }
  
  return 0;
}