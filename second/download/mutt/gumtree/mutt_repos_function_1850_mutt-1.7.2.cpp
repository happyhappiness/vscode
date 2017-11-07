char *
BIND_TEXTDOMAIN_CODESET (domainname, codeset)
     const char *domainname;
     const char *codeset;
{
  set_binding_values (domainname, NULL, &codeset);
  return (char *) codeset;
}