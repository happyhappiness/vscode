char *
dgettext (domainname, msgid)
     const char *domainname;
     const char *msgid;
{
  return dgettext__ (domainname, msgid);
}