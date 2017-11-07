static HEADER *find_parent (ATTACHPTR **idx, short idxlen, BODY *cur, short nattach)
{
  short i;
  HEADER *parent = NULL;
  
  if (cur)
  {
    for (i = 0; i < idxlen; i++)
    {
      if (mutt_is_message_type (idx[i]->content->type, idx[i]->content->subtype) 
	  && is_parent (i, idx, idxlen, cur))
	parent = idx[i]->content->hdr;
      if (idx[i]->content == cur)
	break;
    }
  }
  else if (nattach)
    parent = find_common_parent (idx, idxlen, nattach);
  
  return parent;
}