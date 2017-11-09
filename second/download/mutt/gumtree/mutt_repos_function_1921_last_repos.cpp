char *
ngettext (msgid1, msgid2, n)
     const char *msgid1;
     const char *msgid2;
     unsigned long int n;
{
  return ngettext__ (msgid1, msgid2, n);
}