static ATTACHPTR *find_parent (ATTACH_CONTEXT *actx, BODY *cur, short nattach)
{
  short i;
  ATTACHPTR *parent = NULL;
  
  if (cur)
  {
    for (i = 0; i < actx->idxlen; i++)
    {
      if (mutt_is_message_type (actx->idx[i]->content->type, actx->idx[i]->content->subtype) 
	  && is_parent (i, actx, cur))
	parent = actx->idx[i];
      if (actx->idx[i]->content == cur)
	break;
    }
  }
  else if (nattach)
    parent = find_common_parent (actx, nattach);
  
  return parent;
}