static BODY ** copy_problematic_attachments (FILE *fp,
					     BODY **last, 
					     ATTACHPTR **idx, 
					     short idxlen,
					     short force)
{
  short i;
  
  for (i = 0; i < idxlen; i++)
  {
    if (idx[i]->content->tagged && 
	(force || !mutt_can_decode (idx[i]->content)))
    {
      if (mutt_copy_body (fp, last, idx[i]->content) == -1)
	return NULL;		/* XXXXX - may lead to crashes */
      last = &((*last)->next);
    }
  }
  return last;
}