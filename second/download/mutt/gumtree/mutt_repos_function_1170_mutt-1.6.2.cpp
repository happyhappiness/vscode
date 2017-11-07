void rfc2047_decode_adrlist (ADDRESS *a)
{
  while (a)
  {
    if (a->personal && ((strstr (a->personal, "=?") != NULL) || 
			(AssumedCharset && *AssumedCharset)))
      rfc2047_decode (&a->personal);
    else if (a->group && a->mailbox && (strstr (a->mailbox, "=?") != NULL))
      rfc2047_decode (&a->mailbox);
#ifdef EXACT_ADDRESS
    if (a->val && strstr (a->val, "=?") != NULL)
      rfc2047_decode (&a->val);
#endif
    a = a->next;
  }
}