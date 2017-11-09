char *
DNGETTEXT (domainname, msgid1, msgid2, n)
     const char *domainname;
     const char *msgid1;
     const char *msgid2;
     unsigned long int n;
{
  return DCNGETTEXT (domainname, msgid1, msgid2, n, LC_MESSAGES);
}