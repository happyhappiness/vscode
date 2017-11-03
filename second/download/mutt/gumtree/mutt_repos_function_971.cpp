static short count_tagged_children (ATTACHPTR ** idx, 
				    short idxlen, short i)
{
  short level = idx[i]->level;
  short count = 0;

  while ((++i < idxlen) && (level < idx[i]->level))
    if (idx[i]->content->tagged)
      count++;

  return count;
}