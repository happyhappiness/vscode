char *
DCNGETTEXT (domainname, msgid1, msgid2, n, category)
     const char *domainname;
     const char *msgid1;
     const char *msgid2;
     unsigned long int n;
     int category;
{
  return DCIGETTEXT (domainname, msgid1, msgid2, 1, n, category);
}