static ADDRESS *result_to_addr (QUERY *r)
{
  static ADDRESS tmp;
  
  tmp = *r->addr;
  
  if(!tmp.next && !tmp.personal)
    tmp.personal = r->name;
  
  return &tmp;
}