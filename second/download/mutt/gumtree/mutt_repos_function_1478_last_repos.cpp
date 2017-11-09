const char *_mutt_fmt_pgp_command (char *dest,
				   size_t destlen,
				   size_t col,
                                   int cols,
				   char op,
				   const char *src,
				   const char *prefix,
				   const char *ifstring,
				   const char *elsestring,
				   unsigned long data,
				   format_flag flags)
{
  char fmt[16];
  struct pgp_command_context *cctx = (struct pgp_command_context *) data;
  int optional = (flags & MUTT_FORMAT_OPTIONAL);
  
  switch (op)
  {
    case 'r':
    {
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, NONULL (cctx->ids));
      }
      else if (!cctx->ids)
	optional = 0;
      break;
    }
    
    case 'a':
    {
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, NONULL (cctx->signas));
      }
      else if (!cctx->signas)
	optional = 0;
      break;
    }
    
    case 's':
    {
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, NONULL (cctx->sig_fname));
      }
      else if (!cctx->sig_fname)
	optional = 0;
      break;
    }
    
    case 'f':
    {
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, NONULL (cctx->fname));
      }
      else if (!cctx->fname)
	optional = 0;
      break;
    }
    
    case 'p':
    {
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, cctx->need_passphrase ? "PGPPASSFD=0" : "");
      }
      else if (!cctx->need_passphrase || pgp_use_gpg_agent())
	optional = 0;
      break;
    }
    default:
    {
      *dest = '\0';
      break;
    }
  }

  if (optional)
    mutt_FormatString (dest, destlen, col, cols, ifstring, _mutt_fmt_pgp_command, data, 0);
  else if (flags & MUTT_FORMAT_OPTIONAL)
    mutt_FormatString (dest, destlen, col, cols, elsestring, _mutt_fmt_pgp_command, data, 0);

  return (src);
}