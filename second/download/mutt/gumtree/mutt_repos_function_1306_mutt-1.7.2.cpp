static int can_print (BODY *top, int tag)
{
  char type [STRING];

  for (; top; top = top->next)
  {
    snprintf (type, sizeof (type), "%s/%s", TYPE (top), top->subtype);
    if (!tag || top->tagged)
    {
      if (!rfc1524_mailcap_lookup (top, type, NULL, MUTT_PRINT))
      {
	if (ascii_strcasecmp ("text/plain", top->subtype) &&
	    ascii_strcasecmp ("application/postscript", top->subtype))
	{
	  if (!mutt_can_decode (top))
	  {
	    mutt_error (_("I don't know how to print %s attachments!"), type);
	    return (0);
	  }
	}
      }
    }
    else if (top->parts)
      return (can_print (top->parts, tag));
    if (!tag)
      break;
  }
  return (1);
}