}

/* enter a mutt command */
void mutt_enter_command (void)
{
  BUFFER err, token;
  char buffer[LONG_STRING], errbuf[SHORT_STRING];
  int r;

  buffer[0] = 0;
  if (mutt_get_field (":", buffer, sizeof (buffer), M_COMMAND) != 0 || !buffer[0])
    return;
  err.data = errbuf;
  err.dsize = sizeof (errbuf);
  memset (&token, 0, sizeof (token));
  r = mutt_parse_rc_line (buffer, &token, &err);
  FREE (&token.data);
  if (errbuf[0])
  {
    /* since errbuf could potentially contain printf() sequences in it,
       we must call mutt_error() in this fashion so that vsprintf()
       doesn't expect more arguments that we passed */
    if (r == 0)
      mutt_message ("%s", errbuf);
    else
      mutt_error ("%s", errbuf);
  }
}

void mutt_display_address (ENVELOPE *env)
{
  char *pfx = NULL;
  char buf[SHORT_STRING];
  ADDRESS *adr = NULL;

  adr = mutt_get_address (env, &pfx);

  if (!adr) return;

  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), adr);
  mutt_message ("%s: %s", pfx, buf);
}

static void set_copy_flags (HEADER *hdr, int decode, int decrypt, int *cmflags, int *chflags)
{
  *cmflags = 0;
  *chflags = CH_UPDATE_LEN;
  
#ifdef HAVE_PGP
  if (!decode && decrypt && (hdr->pgp & PGPENCRYPT))
  {
    if (mutt_is_multipart_encrypted(hdr->content))
    {
      *chflags = CH_NONEWLINE | CH_XMIT | CH_MIME;
      *cmflags = M_CM_DECODE_PGP;
    }
    else if (mutt_is_application_pgp(hdr->content) & PGPENCRYPT)
      decode = 1;
  }
#endif

  if (decode)
  {
    *chflags = CH_XMIT | CH_MIME | CH_TXTPLAIN;
    *cmflags = M_CM_DECODE | M_CM_CHARCONV;
  }

  /* respect $weed only if decode doesn't kick in
   * for decrypt.
   */

  if (decode && !decrypt && option (OPTWEED))
  {
    *chflags |= CH_WEED;
    *cmflags |= M_CM_WEED;
  }
}

void _mutt_save_message (HEADER *h, CONTEXT *ctx, int delete, int decode, int decrypt)
{
  int cmflags, chflags;
  
  set_copy_flags (h, decode, decrypt, &cmflags, &chflags);

  if (decode || decrypt)
    mutt_parse_mime_message (Context, h);

  if (mutt_append_message (ctx, Context, h, cmflags, chflags) == 0 && delete)
  {
    mutt_set_flag (Context, h, M_DELETE, 1);
    if (option (OPTDELETEUNTAG))
      mutt_set_flag (Context, h, M_TAG, 0);
  }
}

/* returns 0 if the copy/save was successful, or -1 on error/abort */
int mutt_save_message (HEADER *h, int delete, 
		       int decode, int decrypt, int *redraw)
{
  int i, need_buffy_cleanup;
#ifdef HAVE_PGP
  int need_passphrase = 0;
#endif
  char prompt[SHORT_STRING], buf[_POSIX_PATH_MAX];
  CONTEXT ctx;
  struct stat st;
#ifdef BUFFY_SIZE
  BUFFY *tmp = NULL;
#else
  struct utimbuf ut;
#endif

  *redraw = 0;

  
  snprintf (prompt, sizeof (prompt),
	    decode  ? (delete ? _("Decode-save%s to mailbox") :
