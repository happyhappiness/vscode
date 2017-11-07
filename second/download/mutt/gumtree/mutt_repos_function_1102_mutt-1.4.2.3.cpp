int mutt_is_autoview (BODY *b, const char *type)
{
  LIST *t = AutoViewList;
  char _type[SHORT_STRING];
  int i;

  if (!type)
  {
    snprintf (_type, sizeof (_type), "%s/%s", TYPE (b), b->subtype);
    type = _type;
  }

  if (mutt_needs_mailcap (b))
  {
    if (option (OPTIMPLICITAUTOVIEW))
      return 1;
    
    if (is_mmnoask (type))
      return 1;
  }

  for (; t; t = t->next)
  {
    i = mutt_strlen (t->data) - 1;
    if ((i > 0 && t->data[i-1] == '/' && t->data[i] == '*' && 
	 ascii_strncasecmp (type, t->data, i) == 0) ||
	ascii_strcasecmp (type, t->data) == 0)
      return 1;
  }

  return 0;
}