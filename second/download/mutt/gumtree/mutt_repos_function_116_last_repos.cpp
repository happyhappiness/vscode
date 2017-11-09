const char *mutt_get_name (ADDRESS *a)
{
  ADDRESS *ali;

  if (a)
  {
    if (option (OPTREVALIAS) && (ali = alias_reverse_lookup (a)) && ali->personal)
      return ali->personal;
    else if (a->personal)
      return a->personal;
    else if (a->mailbox)
      return (mutt_addr_for_display (a));
  }
  /* don't return NULL to avoid segfault when printing/comparing */
  return ("");
}