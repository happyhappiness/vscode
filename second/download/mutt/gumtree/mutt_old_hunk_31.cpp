		    _("[-- This %s/%s attachment is not included, --]\n"),
		    TYPE (b->parts), b->parts->subtype);
      state_mark_attach (s);
      state_printf (s, 
		    _("[-- and the indicated access-type %s is unsupported --]\n"),
		    access_type);
      mutt_copy_hdr (s->fpin, s->fpout, ftell (s->fpin), b->parts->offset,
		     (option (OPTWEED) ? (CH_WEED | CH_REORDER) : 0) |
		     CH_DECODE , NULL);
    }
  }
}

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

void mutt_body_handler (BODY *b, STATE *s)
{
  int decode = 0;
  int plaintext = 0;
  FILE *fp = NULL;
  char tempfile[_POSIX_PATH_MAX];
  handler_t handler = NULL;
  long tmpoffset = 0;
  size_t tmplength = 0;
  char type[STRING];

  int oflags = s->flags;
  
  /* first determine which handler to use to process this part */

  snprintf (type, sizeof (type), "%s/%s", TYPE (b), b->subtype);
  if (mutt_is_autoview (b, type))
  {
    rfc1524_entry *entry = rfc1524_new_entry ();

    if (rfc1524_mailcap_lookup (b, type, entry, M_AUTOVIEW))
    {
      handler   = autoview_handler;
      s->flags &= ~M_CHARCONV;
    }
    rfc1524_free_entry (&entry);
  }
  else if (b->type == TYPETEXT)
  {
    if (ascii_strcasecmp ("plain", b->subtype) == 0)
    {
      /* avoid copying this part twice since removing the transfer-encoding is
       * the only operation needed.
       */
      if (ascii_strcasecmp ("flowed", mutt_get_parameter ("format", b->parameter)) == 0)
	handler = text_plain_flowed_handler;
      else
	plaintext = 1;
    }
    else if (ascii_strcasecmp ("enriched", b->subtype) == 0)
      handler = text_enriched_handler;
    else if (ascii_strcasecmp ("rfc822-headers", b->subtype) == 0)
      plaintext = 1;
  }
  else if (b->type == TYPEMESSAGE)
  {
    if(mutt_is_message_type(b->type, b->subtype))
      handler = message_handler;
