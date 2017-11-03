char *
NGETTEXT (msgid1, msgid2, n)
     const char *msgid1;
     const char *msgid2;
     unsigned long int n;
{
  return DCNGETTEXT (NULL, msgid1, msgid2, n, LC_MESSAGES);
}