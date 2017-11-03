static void mutt_set_encoding (BODY *b, CONTENT *info)
{
  char send_charset[SHORT_STRING];

  if (b->type == TYPETEXT)
  {
    char *chsname = mutt_get_body_charset (send_charset, sizeof (send_charset), b);
    if ((info->lobin && ascii_strncasecmp (chsname, "iso-2022", 8)) || info->linemax > 990 || (info->from && option (OPTENCODEFROM)))
      b->encoding = ENCQUOTEDPRINTABLE;
    else if (info->hibin)
      b->encoding = option (OPTALLOW8BIT) ? ENC8BIT : ENCQUOTEDPRINTABLE;
    else
      b->encoding = ENC7BIT;
  }
  else if (b->type == TYPEMESSAGE || b->type == TYPEMULTIPART)
  {
    if (info->lobin || info->hibin)
    {
      if (option (OPTALLOW8BIT) && !info->lobin)
	b->encoding = ENC8BIT;
      else
	mutt_message_to_7bit (b, NULL);
    }
    else
      b->encoding = ENC7BIT;
  }
  else if (b->type == TYPEAPPLICATION && ascii_strcasecmp (b->subtype, "pgp-keys") == 0)
    b->encoding = ENC7BIT;
  else
#if 0
    if (info->lobin || info->hibin || info->binary || info->linemax > 990
	   || info->cr || (/* option (OPTENCODEFROM) && */ info->from))
#endif
  {
    /* Determine which encoding is smaller  */
    if (1.33 * (float)(info->lobin+info->hibin+info->ascii) <
	 3.0 * (float)(info->lobin + info->hibin) + (float)info->ascii)
      b->encoding = ENCBASE64;
    else
      b->encoding = ENCQUOTEDPRINTABLE;
  }
#if 0
  else
    b->encoding = ENC7BIT;
#endif
}