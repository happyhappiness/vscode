static int query_tag (MUTTMENU *menu, int n, int m)
{
  ENTRY *cur = &((ENTRY *) menu->data)[n];
  int ot = cur->tagged;
  
  cur->tagged = m >= 0 ? m : !cur->tagged;
  return cur->tagged - ot;
}