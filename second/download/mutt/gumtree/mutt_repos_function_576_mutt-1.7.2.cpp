static ADDRESS *result_to_addr (QUERY *r)
{
  static ADDRESS *tmp;
  
  if (!(tmp = rfc822_cpy_adr (r->addr, 0)))
    return NULL;
  
  if(!tmp->next && !tmp->personal)
    tmp->personal = safe_strdup (r->name);
  
  mutt_addrlist_to_intl (tmp, NULL);
  return tmp;
}