static BODY ** copy_problematic_attachments (BODY **last, 
					     ATTACH_CONTEXT *actx,
					     short force)
{
  short i;
  
  for (i = 0; i < actx->idxlen; i++)
  {
    if (actx->idx[i]->content->tagged && 
	(force || !mutt_can_decode (actx->idx[i]->content)))
    {
      if (mutt_copy_body (actx->idx[i]->fp, last, actx->idx[i]->content) == -1)
	return NULL;		/* XXXXX - may lead to crashes */
      last = &((*last)->next);
    }
  }
  return last;
}