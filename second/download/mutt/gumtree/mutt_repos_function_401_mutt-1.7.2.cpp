static const char *_mutt_fmt_smime_command (char *dest,
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
  struct smime_command_context *cctx = (struct smime_command_context *) data;
  int optional = (flags & MUTT_FORMAT_OPTIONAL);
  
  switch (op)
  {
    case 'C':
    {
      if (!optional)
      {
	char path[_POSIX_PATH_MAX];
	char buf1[LONG_STRING], buf2[LONG_STRING];
	struct stat sb;

	strfcpy (path, NONULL (SmimeCALocation), sizeof (path));
	mutt_expand_path (path, sizeof (path));
	mutt_quote_filename (buf1, sizeof (buf1), path);

	if (stat (path, &sb) != 0 || !S_ISDIR (sb.st_mode))
	  snprintf (buf2, sizeof (buf2), "-CAfile %s", buf1);
	else
	  snprintf (buf2, sizeof (buf2), "-CApath %s", buf1);
	
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, buf2);
      }
      else if (!SmimeCALocation)
	optional = 0;
      break;
    }
    
    case 'c':
    {           /* certificate (list) */
      if (!optional) {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, NONULL(cctx->certificates));
      }
      else if (!cctx->certificates)
	optional = 0;
      break;
    }
    
    case 'i':
    {           /* intermediate certificates  */
      if (!optional) {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, NONULL(cctx->intermediates));
      }
      else if (!cctx->intermediates)
	optional = 0;
      break;
    }
    
    case 's':
    {           /* detached signature */
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, NONULL (cctx->sig_fname));
      }
      else if (!cctx->sig_fname)
	optional = 0;
      break;
    }
    
    case 'k':
    {           /* private key */
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, NONULL (cctx->key));
      }
      else if (!cctx->key)
	optional = 0;
      break;
    }
    
    case 'a':
    {           /* algorithm for encryption */
      if (!optional) {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, NONULL (cctx->cryptalg));
      }
      else if (!cctx->key)
	optional = 0;
      break;
    }
    
    case 'f':
    {           /* file to process */
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, NONULL (cctx->fname));
      }
      else if (!cctx->fname)
	optional = 0;
      break;
    }
    
    case 'd':
    {           /* algorithm for the signature message digest */
      if (!optional) {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, NONULL (cctx->digestalg));
      }
      else if (!cctx->key)
	optional = 0;
      break;
    }

    default:
      *dest = '\0';
      break;
  }

  if (optional)
    mutt_FormatString (dest, destlen, col, cols, ifstring, _mutt_fmt_smime_command,
		       data, 0);
  else if (flags & MUTT_FORMAT_OPTIONAL)
    mutt_FormatString (dest, destlen, col, cols, elsestring, _mutt_fmt_smime_command,
		       data, 0);

  return (src);
}