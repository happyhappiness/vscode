static int str2scope (const char *p)
{
  if(strequal(p, "one"))
     return LDAP_SCOPE_ONELEVEL;
  if(strequal(p, "onetree"))
     return LDAP_SCOPE_ONELEVEL;
  if(strequal(p, "base"))
     return LDAP_SCOPE_BASE;
  if(strequal(p, "sub"))
     return LDAP_SCOPE_SUBTREE;
  if(strequal( p, "subtree"))
     return LDAP_SCOPE_SUBTREE;
  return (-1);
}