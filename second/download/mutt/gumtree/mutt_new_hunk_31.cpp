		    _("[-- This %s/%s attachment is not included, --]\n"),
		    TYPE (b->parts), b->parts->subtype);
      state_mark_attach (s);
      state_printf (s, 
		    _("[-- and the indicated access-type %s is unsupported --]\n"),
		    access_type);
      mutt_copy_hdr (s->fpin, s->fpout, ftello (s->fpin), b->parts->offset,
		     (option (OPTWEED) ? (CH_WEED | CH_REORDER) : 0) |
		     CH_DECODE | CH_DISPLAY, NULL);
    }
  }
  
  return 0;
}

void mutt_decode_attachment (BODY *b, STATE *s)
{
  int istext = mutt_is_text_part (b);
  iconv_t cd = (iconv_t)(-1);

  if (istext && s->flags & M_CHARCONV)
  {
    char *charset = mutt_get_parameter ("charset", b->parameter);
    if (!charset && AssumedCharset && *AssumedCharset)
      charset = mutt_get_default_charset ();
    if (charset && Charset)
      cd = mutt_iconv_open (Charset, charset, M_ICONV_HOOK_FROM);
  }
  else if (istext && b->charset)
    cd = mutt_iconv_open (Charset, b->charset, M_ICONV_HOOK_FROM);

  fseeko (s->fpin, b->offset, 0);
  switch (b->encoding)
  {
    case ENCQUOTEDPRINTABLE:
      mutt_decode_quoted (s, b->length, istext || ((WithCrypto & APPLICATION_PGP) && mutt_is_application_pgp (b)), cd);
      break;
    case ENCBASE64:
      mutt_decode_base64 (s, b->length, istext || ((WithCrypto & APPLICATION_PGP) && mutt_is_application_pgp (b)), cd);
      break;
    case ENCUUENCODED:
      mutt_decode_uuencoded (s, b->length, istext || ((WithCrypto & APPLICATION_PGP) && mutt_is_application_pgp (b)), cd);
      break;
    default:
      mutt_decode_xbit (s, b->length, istext || ((WithCrypto & APPLICATION_PGP) && mutt_is_application_pgp (b)), cd);
      break;
  }

  if (cd != (iconv_t)(-1))
    iconv_close (cd);
}

/* when generating format=flowed ($text_flowed is set) from format=fixed,
 * strip all trailing spaces to improve interoperability;
 * if $text_flowed is unset, simply verbatim copy input
 */
static int text_plain_handler (BODY *b, STATE *s)
{
  char *buf = NULL;
  size_t l = 0, sz = 0;

  while ((buf = mutt_read_line (buf, &sz, s->fpin, NULL, 0)))
  {
    if (mutt_strcmp (buf, "-- ") != 0 && option (OPTTEXTFLOWED))
    {
      l = mutt_strlen (buf);
      while (l > 0 && buf[l-1] == ' ')
	buf[--l] = 0;
    }
    if (s->prefix)
      state_puts (s->prefix, s);
    state_puts (buf, s);
    state_putc ('\n', s);
  }

  FREE (&buf);
  return 0;
}

int mutt_body_handler (BODY *b, STATE *s)
{
  int decode = 0;
  int plaintext = 0;
  FILE *fp = NULL;
  char tempfile[_POSIX_PATH_MAX];
  handler_t handler = NULL;
  long tmpoffset = 0;
  size_t tmplength = 0;
  int rc = 0;

  int oflags = s->flags;
  
  /* first determine which handler to use to process this part */

  if (mutt_is_autoview (b))
  {
    handler = autoview_handler;
    s->flags &= ~M_CHARCONV;
  }
  else if (b->type == TYPETEXT)
  {
    if (ascii_strcasecmp ("plain", b->subtype) == 0)
    {
      /* avoid copying this part twice since removing the transfer-encoding is
       * the only operation needed.
       */
      if ((WithCrypto & APPLICATION_PGP) && mutt_is_application_pgp (b))
	handler = crypt_pgp_application_pgp_handler;
      else if (option(OPTREFLOWTEXT) && ascii_strcasecmp ("flowed", mutt_get_parameter ("format", b->parameter)) == 0)
	handler = rfc3676_handler;
      else
	handler = text_plain_handler;
    }
    else if (ascii_strcasecmp ("enriched", b->subtype) == 0)
      handler = text_enriched_handler;
    else /* text body type without a handler */
      plaintext = 1;
  }
  else if (b->type == TYPEMESSAGE)
  {
    if(mutt_is_message_type(b->type, b->subtype))
      handler = message_handler;
