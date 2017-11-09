static short check_all_msg (ATTACH_CONTEXT *actx,
			    BODY * cur, short err)
{
  short i;

  if (cur && check_msg (cur, err) == -1)
    return -1;
  else if (!cur)
  {
    for (i = 0; i < actx->idxlen; i++)
    {
      if (actx->idx[i]->content->tagged)
      {
	if (check_msg (actx->idx[i]->content, err) == -1)
	  return -1;
      }
    }
  }
  return 0;
}