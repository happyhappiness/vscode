void rfc2047_decode_adrlist (ADDRESS *a)
{
  while (a)
  {
    if (a->personal && strstr (a->personal, "=?") != NULL)
      rfc2047_decode (&a->personal);
#ifdef EXACT_ADDRESS
    if (a->val && strstr (a->val, "=?") != NULL)
      rfc2047_decode (&a->val);
#endif
    a = a->next;
  }
}