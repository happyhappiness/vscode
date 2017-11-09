static int can_print (ATTACH_CONTEXT *actx, BODY *top, int tag)
{
  char type [STRING];
  int i;

  for (i = 0; !tag || i < actx->idxlen; i++)
  {
    if (tag)
      top = actx->idx[i]->content;
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
    if (!tag)
      break;
  }
  return (1);
}