int mutt_tag_attach (MUTTMENU *menu, int n, int m)
{
  ATTACH_CONTEXT *actx = (ATTACH_CONTEXT *)menu->data;
  BODY *cur = actx->idx[actx->v2r[n]]->content;
  int ot = cur->tagged;

  cur->tagged = (m >= 0 ? m : !cur->tagged);
  return cur->tagged - ot;
}