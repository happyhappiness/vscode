static HEADER *find_common_parent (ATTACHPTR ** idx, short idxlen,
				   short nattach)
{
  short i;
  short nchildren;

  for (i = 0; i < idxlen; i++)
    if (idx[i]->content->tagged)
      break;
  
  while (--i >= 0)
  {
    if (mutt_is_message_type (idx[i]->content->type, idx[i]->content->subtype))
    {
      nchildren = count_tagged_children (idx, idxlen, i);
      if (nchildren == nattach)
	return idx[i]->content->hdr;
    }
  }

  return NULL;
}