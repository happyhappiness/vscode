static short count_tagged (ATTACHPTR **idx, short idxlen)
{
  short count = 0;
  short i;
  
  for (i = 0; i < idxlen; i++)
    if (idx[i]->content->tagged)
      count++;
  
  return count;
}