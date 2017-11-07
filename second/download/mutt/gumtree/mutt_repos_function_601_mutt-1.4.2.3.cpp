static short check_all_msg (ATTACHPTR ** idx, short idxlen,
			    BODY * cur, short err)
{
  short i;

  if (cur && check_msg (cur, err) == -1)
    return -1;
  else if (!cur)
  {
    for (i = 0; i < idxlen; i++)
    {
      if (idx[i]->content->tagged)
      {
	if (check_msg (idx[i]->content, err) == -1)
	  return -1;
      }
    }
  }
  return 0;
}