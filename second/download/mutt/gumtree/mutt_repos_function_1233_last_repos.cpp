void rfc2047_encode_adrlist (ADDRESS *addr, const char *tag)
{
  ADDRESS *ptr = addr;
  int col = tag ? strlen (tag) + 2 : 32;
  
  while (ptr)
  {
    if (ptr->personal)
      _rfc2047_encode_string (&ptr->personal, 1, col);
    else if (ptr->group && ptr->mailbox)
      _rfc2047_encode_string (&ptr->mailbox, 1, col);
#ifdef EXACT_ADDRESS
    if (ptr->val)
      _rfc2047_encode_string (&ptr->val, 1, col);
#endif
    ptr = ptr->next;
  }
}