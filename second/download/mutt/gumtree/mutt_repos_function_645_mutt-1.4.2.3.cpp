void mutt_decode_attachment (BODY *b, STATE *s)
{
  int istext = mutt_is_text_type (b->type, b->subtype);
  iconv_t cd = (iconv_t)(-1);

  if (istext && s->flags & M_CHARCONV)
  {
    char *charset = mutt_get_parameter ("charset", b->parameter);
    if (charset && Charset)
      cd = mutt_iconv_open (Charset, charset, M_ICONV_HOOK_FROM);
  }

  fseek (s->fpin, b->offset, 0);
  switch (b->encoding)
  {
    case ENCQUOTEDPRINTABLE:
      mutt_decode_quoted (s, b->length, istext, cd);
      break;
    case ENCBASE64:
      mutt_decode_base64 (s, b->length, istext, cd);
      break;
    case ENCUUENCODED:
      mutt_decode_uuencoded (s, b->length, istext, cd);
      break;
    default:
      mutt_decode_xbit (s, b->length, istext, cd);
      break;
  }

  if (cd != (iconv_t)(-1))
    iconv_close (cd);
}