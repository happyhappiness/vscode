void mutt_update_tree (ATTACHPTR **idx, short idxlen)
{
  char buf[STRING];
  char *s;
  int x;

  for (x = 0; x < idxlen; x++)
  {
    idx[x]->num = x;
    if (2 * (idx[x]->level + 2) < sizeof (buf))
    {
      if (idx[x]->level)
      {
	s = buf + 2 * (idx[x]->level - 1);
	*s++ = (idx[x]->content->next) ? MUTT_TREE_LTEE : MUTT_TREE_LLCORNER;
	*s++ = MUTT_TREE_HLINE;
	*s++ = MUTT_TREE_RARROW;
      }
      else
	s = buf;
      *s = 0;
    }

    if (idx[x]->tree)
    {
      if (mutt_strcmp (idx[x]->tree, buf) != 0)
	mutt_str_replace (&idx[x]->tree, buf);
    }
    else
      idx[x]->tree = safe_strdup (buf);

    if (2 * (idx[x]->level + 2) < sizeof (buf) && idx[x]->level)
    {
      s = buf + 2 * (idx[x]->level - 1);
      *s++ = (idx[x]->content->next) ? '\005' : '\006';
      *s++ = '\006';
    }
  }
}