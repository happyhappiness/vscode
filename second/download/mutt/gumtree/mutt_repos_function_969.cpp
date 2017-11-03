static short check_can_decode (ATTACHPTR ** idx, short idxlen, 
			      BODY * cur)
{
  short i;

  if (cur)
    return mutt_can_decode (cur);

  for (i = 0; i < idxlen; i++)
    if (idx[i]->content->tagged && !mutt_can_decode (idx[i]->content))
      return 0;

  return 1;
}