char *
GETTEXT (msgid)
     const char *msgid;
{
  return DCGETTEXT (NULL, msgid, LC_MESSAGES);
}