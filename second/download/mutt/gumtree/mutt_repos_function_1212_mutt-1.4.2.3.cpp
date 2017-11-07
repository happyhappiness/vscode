char *
dcgettext (domainname, msgid, category)
     const char *domainname;
     const char *msgid;
     int category;
{
  return dcgettext__ (domainname, msgid, category);
}