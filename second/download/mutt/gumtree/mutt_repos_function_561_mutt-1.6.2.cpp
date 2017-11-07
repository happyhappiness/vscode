static int query_search (MUTTMENU *m, regex_t *re, int n)
{
  ENTRY *table = (ENTRY *) m->data;

  if (table[n].data->name && !regexec (re, table[n].data->name, 0, NULL, 0))
    return 0;
  if (table[n].data->other && !regexec (re, table[n].data->other, 0, NULL, 0))
    return 0;
  if (table[n].data->addr)
  {
    if (table[n].data->addr->personal && 
	!regexec (re, table[n].data->addr->personal, 0, NULL, 0))
      return 0;
    if (table[n].data->addr->mailbox &&
	!regexec (re, table[n].data->addr->mailbox, 0, NULL, 0))
      return 0;
#ifdef EXACT_ADDRESS
    if (table[n].data->addr->val &&
	!regexec (re, table[n].data->addr->val, 0, NULL, 0))
      return 0;
#endif
  }
  
  return REG_NOMATCH;
}