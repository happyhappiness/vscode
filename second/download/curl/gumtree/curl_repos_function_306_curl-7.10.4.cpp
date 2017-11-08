static void hostcache_fixoffset(struct hostent *h, int offset)
{
  int i=0;
  h->h_name=(char *)((long)h->h_name+offset);
  h->h_aliases=(char **)((long)h->h_aliases+offset);
  while(h->h_aliases[i]) {
    h->h_aliases[i]=(char *)((long)h->h_aliases[i]+offset);
    i++;
  }
  h->h_addr_list=(char **)((long)h->h_addr_list+offset);
  i=0;
  while(h->h_addr_list[i]) {
    h->h_addr_list[i]=(char *)((long)h->h_addr_list[i]+offset);
    i++;
  }
}