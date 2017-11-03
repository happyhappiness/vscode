int mutt_tag_attach (MUTTMENU *menu, int n, int m)
{
  BODY *cur = ((ATTACHPTR **) menu->data)[n]->content;
  int ot = cur->tagged;
  
  cur->tagged = (m >= 0 ? m : !cur->tagged);
  return cur->tagged - ot;
}