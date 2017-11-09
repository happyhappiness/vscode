const char *mutt_attach_fmt (char *dest,
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
  char tmp[SHORT_STRING];
  char charset[SHORT_STRING];
  ATTACHPTR *aptr = (ATTACHPTR *) data;
  int optional = (flags & MUTT_FORMAT_OPTIONAL);
  size_t l;
  
  switch (op)
  {
    case 'C':
      if (!optional)
      {
	if (mutt_is_text_part (aptr->content) &&
	    mutt_get_body_charset (charset, sizeof (charset), aptr->content))
	  mutt_format_s (dest, destlen, prefix, charset);
	else
	  mutt_format_s (dest, destlen, prefix, "");
      }
      else if (!mutt_is_text_part (aptr->content) ||
	       !mutt_get_body_charset (charset, sizeof (charset), aptr->content))
        optional = 0;
      break;
    case 'c':
      /* XXX */
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sc", prefix);
	snprintf (dest, destlen, fmt, aptr->content->type != TYPETEXT ||
		  aptr->content->noconv ? 'n' : 'c');
      }
      else if (aptr->content->type != TYPETEXT || aptr->content->noconv)
        optional = 0;
      break;
    case 'd':
      if(!optional)
      {
	if (aptr->content->description)
	{
	  mutt_format_s (dest, destlen, prefix, aptr->content->description);
	  break;
	}
	if (mutt_is_message_type(aptr->content->type, aptr->content->subtype) &&
	    MsgFmt && aptr->content->hdr)
	{
	  char s[SHORT_STRING];
	  _mutt_make_string (s, sizeof (s), MsgFmt, NULL, aptr->content->hdr,
			     MUTT_FORMAT_FORCESUBJ | MUTT_FORMAT_MAKEPRINT | MUTT_FORMAT_ARROWCURSOR);
	  if (*s)
	  {
	    mutt_format_s (dest, destlen, prefix, s);
	    break;
	  }
	}
        if (!aptr->content->d_filename && !aptr->content->filename)
	{
	  mutt_format_s (dest, destlen, prefix, "<no description>");
	  break;
	}
      }
      else if(aptr->content->description || 
	      (mutt_is_message_type (aptr->content->type, aptr->content->subtype)
	      && MsgFmt && aptr->content->hdr))
        break;
    /* FALLS THROUGH TO 'F' */
    case 'F':
      if (!optional)
      {
        if (aptr->content->d_filename)
        {
          mutt_format_s (dest, destlen, prefix, aptr->content->d_filename);
          break;
        }
      }
      else if (!aptr->content->d_filename && !aptr->content->filename)
      {
        optional = 0;
        break;
      }
    /* FALLS THROUGH TO 'f' */
    case 'f':
      if(!optional)
      {
	if (aptr->content->filename && *aptr->content->filename == '/')
	{
	  char path[_POSIX_PATH_MAX];
	  
	  strfcpy (path, aptr->content->filename, sizeof (path));
	  mutt_pretty_mailbox (path, sizeof (path));
	  mutt_format_s (dest, destlen, prefix, path);
	}
	else
	  mutt_format_s (dest, destlen, prefix, NONULL (aptr->content->filename));
      }
      else if(!aptr->content->filename)
        optional = 0;
      break;
    case 'D':
      if(!optional)
	snprintf (dest, destlen, "%c", aptr->content->deleted ? 'D' : ' ');
      else if(!aptr->content->deleted)
        optional = 0;
      break;
    case 'e':
      if(!optional)
	mutt_format_s (dest, destlen, prefix,
		      ENCODING (aptr->content->encoding));
      break;
    case 'I':
      if (!optional)
      {
	const char dispchar[] = { 'I', 'A', 'F', '-' };
	char ch;

	if (aptr->content->disposition < sizeof(dispchar))
	  ch = dispchar[aptr->content->disposition];
	else
	{
	  dprint(1, (debugfile, "ERROR: invalid content-disposition %d\n", aptr->content->disposition));
	  ch = '!';
	}
	snprintf (dest, destlen, "%c", ch);
      }
      break;
    case 'm':
      if(!optional)
	mutt_format_s (dest, destlen, prefix, TYPE (aptr->content));
      break;
    case 'M':
      if(!optional)
	mutt_format_s (dest, destlen, prefix, aptr->content->subtype);
      else if(!aptr->content->subtype)
        optional = 0;
      break;
    case 'n':
      if(!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (dest, destlen, fmt, aptr->num + 1);
      }
      break;
    case 'Q':
      if (optional)
        optional = aptr->content->attach_qualifies;
      else {
	    snprintf (fmt, sizeof (fmt), "%%%sc", prefix);
        mutt_format_s (dest, destlen, fmt, "Q");
      }
      break;
    case 's':
      if (flags & MUTT_FORMAT_STAT_FILE)
      {
	struct stat st;
	stat (aptr->content->filename, &st);
	l = st.st_size;
      }
      else
        l = aptr->content->length;
      
      if(!optional)
      {
	mutt_pretty_size (tmp, sizeof(tmp), l);
	mutt_format_s (dest, destlen, prefix, tmp);
      }
      else if (l == 0)
        optional = 0;

      break;
    case 't':
      if(!optional)
        snprintf (dest, destlen, "%c", aptr->content->tagged ? '*' : ' ');
      else if(!aptr->content->tagged)
        optional = 0;
      break;
    case 'T':
      if(!optional)
	mutt_format_s_tree (dest, destlen, prefix, NONULL (aptr->tree));
      else if (!aptr->tree)
        optional = 0;
      break;
    case 'u':
      if(!optional)
        snprintf (dest, destlen, "%c", aptr->content->unlink ? '-' : ' ');
      else if (!aptr->content->unlink)
        optional = 0;
      break;
    case 'X':
      if (optional)
        optional = (aptr->content->attach_count + aptr->content->attach_qualifies) != 0;
      else
      {
        snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
        snprintf (dest, destlen, fmt, aptr->content->attach_count + aptr->content->attach_qualifies);
      }
      break;
    default:
      *dest = 0;
  }
  
  if (optional)
    mutt_FormatString (dest, destlen, col, cols, ifstring, mutt_attach_fmt, data, 0);
  else if (flags & MUTT_FORMAT_OPTIONAL)
    mutt_FormatString (dest, destlen, col, cols, elsestring, mutt_attach_fmt, data, 0);
  return (src);
}