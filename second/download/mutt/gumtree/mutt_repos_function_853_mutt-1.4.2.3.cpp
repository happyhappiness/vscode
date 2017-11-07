ADDRESS *rfc822_cpy_adr_real (ADDRESS *addr)
{
  ADDRESS *p = rfc822_new_address ();

#ifdef EXACT_ADDRESS
  p->val = safe_strdup (addr->val);
#endif
  p->personal = safe_strdup (addr->personal);
  p->mailbox = safe_strdup (addr->mailbox);
  p->group = addr->group;
  return p;
}