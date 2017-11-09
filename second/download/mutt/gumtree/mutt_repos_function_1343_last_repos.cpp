void mutt_update_tree (ATTACH_CONTEXT *actx)
{
  char buf[STRING];
  char *s;
  int rindex, vindex;

  mutt_update_v2r (actx);

  for (vindex = 0; vindex < actx->vcount; vindex++)
  {
    rindex = actx->v2r[vindex];
    actx->idx[rindex]->num = vindex;
    if (2 * (actx->idx[rindex]->level + 2) < sizeof (buf))
    {
      if (actx->idx[rindex]->level)
      {
	s = buf + 2 * (actx->idx[rindex]->level - 1);
	*s++ = (actx->idx[rindex]->content->next) ? MUTT_TREE_LTEE : MUTT_TREE_LLCORNER;
	*s++ = MUTT_TREE_HLINE;
	*s++ = MUTT_TREE_RARROW;
      }
      else
	s = buf;
      *s = 0;
    }

    if (actx->idx[rindex]->tree)
    {
      if (mutt_strcmp (actx->idx[rindex]->tree, buf) != 0)
	mutt_str_replace (&actx->idx[rindex]->tree, buf);
    }
    else
      actx->idx[rindex]->tree = safe_strdup (buf);

    if (2 * (actx->idx[rindex]->level + 2) < sizeof (buf) && actx->idx[rindex]->level)
    {
      s = buf + 2 * (actx->idx[rindex]->level - 1);
      *s++ = (actx->idx[rindex]->content->next) ? '\005' : '\006';
      *s++ = '\006';
    }
  }
}