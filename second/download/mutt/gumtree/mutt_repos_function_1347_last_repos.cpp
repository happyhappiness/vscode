int mutt_is_message_type (int type, const char *subtype)
{
  if (type != TYPEMESSAGE)
    return 0;

  subtype = NONULL(subtype);
  return (ascii_strcasecmp (subtype, "rfc822") == 0 || ascii_strcasecmp (subtype, "news") == 0);
}