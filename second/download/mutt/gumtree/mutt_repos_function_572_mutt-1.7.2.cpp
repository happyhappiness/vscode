static int alias_tag (MUTTMENU *menu, int n, int m)
{
  ALIAS *cur = ((ALIAS **) menu->data)[n];
  int ot = cur->tagged;
  
  cur->tagged = (m >= 0 ? m : !cur->tagged);
  
  return cur->tagged - ot;
}