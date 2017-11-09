static int str2scope(const char *p)
{
  if(strcasecompare(p, "one"))
    return LDAP_SCOPE_ONELEVEL;
  if(strcasecompare(p, "onetree"))
    return LDAP_SCOPE_ONELEVEL;
  if(strcasecompare(p, "base"))
    return LDAP_SCOPE_BASE;
  if(strcasecompare(p, "sub"))
    return LDAP_SCOPE_SUBTREE;
  if(strcasecompare(p, "subtree"))
    return LDAP_SCOPE_SUBTREE;
  return (-1);
}