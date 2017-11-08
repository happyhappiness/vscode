static int
msg_search (CONTEXT *ctx, regex_t *rx, char *buf, size_t blen, int op, int msgno)
{
  char tempfile[_POSIX_PATH_MAX];
  MESSAGE *msg = NULL;
  STATE s;
  struct stat st;
  FILE *fp = NULL;
  long lng = 0;
  int match = 0;
  HEADER *h = ctx->hdrs[msgno];

  if ((msg = mx_open_message (ctx, msgno)) != NULL)
  {
    if (option (OPTTHOROUGHSRC))
    {
      /* decode the header / body */
      memset (&s, 0, sizeof (s));
      s.fpin = msg->fp;
      s.flags = M_CHARCONV;
      mutt_mktemp (tempfile);
      if ((s.fpout = safe_fopen (tempfile, "w+")) == NULL)
      {
	mutt_perror (tempfile);
	return (0);
      }

      if (op != M_BODY)
	mutt_copy_header (msg->fp, h, s.fpout, CH_FROM | CH_DECODE, NULL);

      if (op != M_HEADER)
      {
	mutt_parse_mime_message (ctx, h);



#ifdef HAVE_PGP
	if (h->pgp & PGPENCRYPT && !pgp_valid_passphrase())
	{
	  mx_close_message (&msg);
	  if (fp)
	  {
	    fclose (fp);
	    unlink (tempfile);
	  }
	  return (0);
	}
#endif



	fseek (msg->fp, h->offset, 0);
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
      if (op != M_BODY)
      {
	fseek (fp, h->offset, 0);
	lng = h->content->offset - h->offset;
      }
      if (op != M_HEADER)
      {
	if (op == M_BODY)
	  fseek (fp, h->content->offset, 0);
	lng += h->content->length;
      }
    }

    /* search the file "fp" */
    while (lng > 0)
    {
      if (fgets (buf, blen - 1, fp) == NULL)
	break; /* don't loop forever */
      if (regexec (rx, buf, 0, NULL, 0) == 0)
      {
	match = 1;
	break;
      }
      lng -= mutt_strlen (buf);
    }
    
    mx_close_message (&msg);

    if (option (OPTTHOROUGHSRC))
    {
      fclose (fp);
      unlink (tempfile);
    }
  }

  return match;
}