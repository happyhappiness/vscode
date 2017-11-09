static ATTACHPTR *find_common_parent (ATTACH_CONTEXT *actx, short nattach)
{
  short i;
  short nchildren;

  for (i = 0; i < actx->idxlen; i++)
    if (actx->idx[i]->content->tagged)
      break;
  
  while (--i >= 0)
  {
    if (mutt_is_message_type (actx->idx[i]->content->type, actx->idx[i]->content->subtype))
    {
      nchildren = count_tagged_children (actx, i);
      if (nchildren == nattach)
	return actx->idx[i];
    }
  }

  return NULL;
}