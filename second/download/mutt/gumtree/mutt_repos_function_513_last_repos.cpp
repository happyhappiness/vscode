void mutt_parse_part (FILE *fp, BODY *b)
{
  char *bound = 0;

  switch (b->type)
  {
    case TYPEMULTIPART:
#ifdef SUN_ATTACHMENT
      if ( !ascii_strcasecmp (b->subtype, "x-sun-attachment") )
          bound = "--------";
      else
#endif
          bound = mutt_get_parameter ("boundary", b->parameter);

      fseeko (fp, b->offset, SEEK_SET);
      b->parts =  mutt_parse_multipart (fp, bound, 
					b->offset + b->length,
					ascii_strcasecmp ("digest", b->subtype) == 0);
      break;

    case TYPEMESSAGE:
      if (b->subtype)
      {
	fseeko (fp, b->offset, SEEK_SET);
	if (mutt_is_message_type(b->type, b->subtype))
	  b->parts = mutt_parse_messageRFC822 (fp, b);
	else if (ascii_strcasecmp (b->subtype, "external-body") == 0)
	  b->parts = mutt_read_mime_header (fp, 0);
	else
	  return;
      }
      break;

    default:
      return;
  }

  /* try to recover from parsing error */
  if (!b->parts)
  {
    b->type = TYPETEXT;
    mutt_str_replace (&b->subtype, "plain");
  }
}