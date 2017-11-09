static void attach_collapse (ATTACH_CONTEXT *actx, MUTTMENU *menu)
{
  int rindex, curlevel;

  CURATTACH->content->collapsed = !CURATTACH->content->collapsed;
  /* When expanding, expand all the children too */
  if (CURATTACH->content->collapsed)
    return;

  curlevel = CURATTACH->level;
  rindex = actx->v2r[menu->current] + 1;

  while ((rindex < actx->idxlen) &&
         (actx->idx[rindex]->level > curlevel))
  {
    if (option (OPTDIGESTCOLLAPSE) &&
        actx->idx[rindex]->content->type == TYPEMULTIPART &&
	!ascii_strcasecmp (actx->idx[rindex]->content->subtype, "digest"))
      actx->idx[rindex]->content->collapsed = 1;
    else
      actx->idx[rindex]->content->collapsed = 0;
    rindex++;
  }
}