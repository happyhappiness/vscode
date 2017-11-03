char *
dcngettext (domainname, msgid1, msgid2, n, category)
     const char *domainname;
     const char *msgid1;
     const char *msgid2;
     unsigned long int n;
     int category;
{
  return dcngettext__ (domainname, msgid1, msgid2, n, category);
}