static void rfc2231_list_insert (struct rfc2231_parameter **list,
				 struct rfc2231_parameter *par)
{
  struct rfc2231_parameter **last = list;
  struct rfc2231_parameter *p = *list, *q;
  int c;
  
  while (p)
  {
    last = &p->next;
    q = p; p = p->next;

    c = strcmp (par->value, q->value);
    if ((c > 0) || (c == 0 && par->index >= q->index))
      break;
  }
  
  par->next = p;
  *last = par;
}