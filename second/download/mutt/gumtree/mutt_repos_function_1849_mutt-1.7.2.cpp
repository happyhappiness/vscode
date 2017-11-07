char *
BINDTEXTDOMAIN (domainname, dirname)
     const char *domainname;
     const char *dirname;
{
  set_binding_values (domainname, &dirname, NULL);
  return (char *) dirname;
}