static int str2scope (const char *p)
{
  if (!stricmp(p, "one"))
     return LDAP_SCOPE_ONELEVEL;
  if (!stricmp(p, "onetree"))
     return LDAP_SCOPE_ONELEVEL;
  if (!stricmp(p, "base"))
     return LDAP_SCOPE_BASE;
  if (!stricmp(p, "sub"))
     return LDAP_SCOPE_SUBTREE;
  if (!stricmp( p, "subtree"))
     return LDAP_SCOPE_SUBTREE;
  return (-1);
}