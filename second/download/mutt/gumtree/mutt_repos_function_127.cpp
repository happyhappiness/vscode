static int
msg_search (CONTEXT *ctx, pattern_t* pat, int msgno)
{
  char tempfile[_POSIX_PATH_MAX];
  MESSAGE *msg = NULL;
  STATE s;
  struct stat st;
  FILE *fp = NULL;
  long lng = 0;
  int match = 0;
  HEADER *h = ctx->hdrs[msgno];
  char *buf;
  size_t blen;

  if ((msg = mx_open_message (ctx, msgno)) != NULL)
  {
    if (option (OPTTHOROUGHSRC))
    {
      /* decode the header / body */
      memset (&s, 0, sizeof (s));
      s.fpin = msg->fp;
      s.flags = MUTT_CHARCONV;
      mutt_mktemp (tempfile, sizeof (tempfile));
      if ((s.fpout = safe_fopen (tempfile, "w+")) == NULL)
      {
	mutt_perror (tempfile);
	return (0);
      }

      if (pat->op != MUTT_BODY)
	mutt_copy_header (msg->fp, h, s.fpout, CH_FROM | CH_DECODE, NULL);

      if (pat->op != MUTT_HEADER)
      {
	mutt_parse_mime_message (ctx, h);

	if (WithCrypto && (h->security & ENCRYPT)
            && !crypt_valid_passphrase(h->security))
	{
	  mx_close_message (ctx, &msg);
	  if (s.fpout)
	  {
	    safe_fclose (&s.fpout);
	    unlink (tempfile);
	  }
	  return (0);
	}

	fseeko (msg->fp, h->offset, 0);
	mutt_body_handler (h->content, &s);
      }

      fp = s.fpout;
      fflush (fp);
      fseek (fp, 0, 0);
      fstat (fileno (fp), &st);
      lng = (long) st.st_size;
    }
    else
    {
      /* raw header / body */
      fp = msg->fp;
      if (pat->op != MUTT_BODY)
      {
	fseeko (fp, h->offset, 0);
	lng = h->content->offset - h->offset;
      }
      if (pat->op != MUTT_HEADER)
      {
	if (pat->op == MUTT_BODY)
	  fseeko (fp, h->content->offset, 0);
	lng += h->content->length;
      }
    }

    blen = STRING;
    buf = safe_malloc (blen);

    /* search the file "fp" */
    while (lng > 0)
    {
      if (pat->op == MUTT_HEADER)
      {
	if (*(buf = mutt_read_rfc822_line (fp, buf, &blen)) == '\0')
	  break;
      }
      else if (fgets (buf, blen - 1, fp) == NULL)
	break; /* don't loop forever */
      if (patmatch (pat, buf) == 0)
      {
	match = 1;
	break;
      }
      lng -= mutt_strlen (buf);
    }

    FREE (&buf);
    
    mx_close_message (ctx, &msg);

    if (option (OPTTHOROUGHSRC))
    {
      safe_fclose (&fp);
      unlink (tempfile);
    }
  }

  return match;
}