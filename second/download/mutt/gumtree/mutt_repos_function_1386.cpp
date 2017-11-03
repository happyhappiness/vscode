void mutt_FormatString (char *dest,		/* output buffer */
			size_t destlen,		/* output buffer len */
			size_t col,		/* starting column (nonzero when called recursively) */
                        int cols,               /* maximum columns */
			const char *src,	/* template string */
			format_t *callback,	/* callback for processing */
			unsigned long data,	/* callback data */
			format_flag flags)	/* callback flags */
{
  char prefix[SHORT_STRING], buf[LONG_STRING], *cp, *wptr = dest, ch;
  char ifstring[SHORT_STRING], elsestring[SHORT_STRING];
  size_t wlen, count, len, wid;
  pid_t pid;
  FILE *filter;
  int n;
  char *recycler;

  prefix[0] = '\0';
  destlen--; /* save room for the terminal \0 */
  wlen = ((flags & MUTT_FORMAT_ARROWCURSOR) && option (OPTARROWCURSOR)) ? 3 : 0;
  col += wlen;

  if ((flags & MUTT_FORMAT_NOFILTER) == 0)
  {
    int off = -1;

    /* Do not consider filters if no pipe at end */
    n = mutt_strlen(src);
    if (n > 1 && src[n-1] == '|')
    {
      /* Scan backwards for backslashes */
      off = n;
      while (off > 0 && src[off-2] == '\\')
        off--;
    }

    /* If number of backslashes is even, the pipe is real. */
    /* n-off is the number of backslashes. */
    if (off > 0 && ((n-off) % 2) == 0)
    {
      BUFFER *srcbuf, *word, *command;
      char    srccopy[LONG_STRING];
#ifdef DEBUG
      int     i = 0;
#endif

      dprint(3, (debugfile, "fmtpipe = %s\n", src));

      strncpy(srccopy, src, n);
      srccopy[n-1] = '\0';

      /* prepare BUFFERs */
      srcbuf = mutt_buffer_from (srccopy);
      srcbuf->dptr = srcbuf->data;
      word = mutt_buffer_new ();
      command = mutt_buffer_new ();

      /* Iterate expansions across successive arguments */
      do {
        char *p;

        /* Extract the command name and copy to command line */
        dprint(3, (debugfile, "fmtpipe +++: %s\n", srcbuf->dptr));
        if (word->data)
          *word->data = '\0';
        mutt_extract_token(word, srcbuf, 0);
        dprint(3, (debugfile, "fmtpipe %2d: %s\n", i++, word->data));
        mutt_buffer_addch(command, '\'');
        mutt_FormatString(buf, sizeof(buf), 0, cols, word->data, callback, data,
                          flags | MUTT_FORMAT_NOFILTER);
        for (p = buf; p && *p; p++)
        {
          if (*p == '\'')
            /* shell quoting doesn't permit escaping a single quote within
             * single-quoted material.  double-quoting instead will lead
             * shell variable expansions, so break out of the single-quoted
             * span, insert a double-quoted single quote, and resume. */
            mutt_buffer_addstr(command, "'\"'\"'");
          else
            mutt_buffer_addch(command, *p);
        }
        mutt_buffer_addch(command, '\'');
        mutt_buffer_addch(command, ' ');
      } while (MoreArgs(srcbuf));

      dprint(3, (debugfile, "fmtpipe > %s\n", command->data));

      col -= wlen;	/* reset to passed in value */
      wptr = dest;      /* reset write ptr */
      wlen = ((flags & MUTT_FORMAT_ARROWCURSOR) && option (OPTARROWCURSOR)) ? 3 : 0;
      if ((pid = mutt_create_filter(command->data, NULL, &filter, NULL)) != -1)
      {
	int rc;

        n = fread(dest, 1, destlen /* already decremented */, filter);
        safe_fclose (&filter);
	rc = mutt_wait_filter(pid);
	if (rc != 0)
	  dprint(1, (debugfile, "format pipe command exited code %d\n", rc));
	if (n > 0) {
	  dest[n] = 0;
	  while ((n > 0) && (dest[n-1] == '\n' || dest[n-1] == '\r'))
	    dest[--n] = '\0';
	  dprint(3, (debugfile, "fmtpipe < %s\n", dest));

	  /* If the result ends with '%', this indicates that the filter
	   * generated %-tokens that mutt can expand.  Eliminate the '%'
	   * marker and recycle the string through mutt_FormatString().
	   * To literally end with "%", use "%%". */
	  if ((n > 0) && dest[n-1] == '%')
	  {
	    --n;
	    dest[n] = '\0';               /* remove '%' */
	    if ((n > 0) && dest[n-1] != '%')
	    {
	      recycler = safe_strdup(dest);
	      if (recycler)
	      {
		/* destlen is decremented at the start of this function
		 * to save space for the terminal nul char.  We can add
		 * it back for the recursive call since the expansion of
		 * format pipes does not try to append a nul itself.
		 */
		mutt_FormatString(dest, destlen+1, col, cols, recycler, callback, data, flags);
		FREE(&recycler);
	      }
	    }
	  }
	}
	else
	{
	  /* read error */
	  dprint(1, (debugfile, "error reading from fmtpipe: %s (errno=%d)\n", strerror(errno), errno));
	  *wptr = 0;
	}
      }
      else
      {
        /* Filter failed; erase write buffer */
        *wptr = '\0';
      }

      mutt_buffer_free(&command);
      mutt_buffer_free(&srcbuf);
      mutt_buffer_free(&word);
      return;
    }
  }

  while (*src && wlen < destlen)
  {
    if (*src == '%')
    {
      if (*++src == '%')
      {
	*wptr++ = '%';
	wlen++;
	col++;
	src++;
	continue;
      }

      if (*src == '?')
      {
	flags |= MUTT_FORMAT_OPTIONAL;
	src++;
      }
      else
      {
	flags &= ~MUTT_FORMAT_OPTIONAL;

	/* eat the format string */
	cp = prefix;
	count = 0;
	while (count < sizeof (prefix) &&
	       (isdigit ((unsigned char) *src) || *src == '.' || *src == '-' || *src == '='))
	{
	  *cp++ = *src++;
	  count++;
	}
	*cp = 0;
      }

      if (!*src)
	break; /* bad format */

      ch = *src++; /* save the character to switch on */

      if (flags & MUTT_FORMAT_OPTIONAL)
      {
        if (*src != '?')
          break; /* bad format */
        src++;

        /* eat the `if' part of the string */
        cp = ifstring;
	count = 0;
        while (count < sizeof (ifstring) && *src && *src != '?' && *src != '&')
	{
          *cp++ = *src++;
	  count++;
	}
        *cp = 0;

	/* eat the `else' part of the string (optional) */
	if (*src == '&')
	  src++; /* skip the & */
	cp = elsestring;
	count = 0;
	while (count < sizeof (elsestring) && *src && *src != '?')
	{
	  *cp++ = *src++;
	  count++;
	}
	*cp = 0;

	if (!*src)
	  break; /* bad format */

        src++; /* move past the trailing `?' */
      }

      /* handle generic cases first */
      if (ch == '>' || ch == '*')
      {
	/* %>X: right justify to EOL, left takes precedence
	 * %*X: right justify to EOL, right takes precedence */
	int soft = ch == '*';
	int pl, pw;
	if ((pl = mutt_charlen (src, &pw)) <= 0)
	  pl = pw = 1;

	/* see if there's room to add content, else ignore */
	if ((col < cols && wlen < destlen) || soft)
	{
	  int pad;

	  /* get contents after padding */
	  mutt_FormatString (buf, sizeof (buf), 0, cols, src + pl, callback, data, flags);
	  len = mutt_strlen (buf);
	  wid = mutt_strwidth (buf);

	  pad = (cols - col - wid) / pw;
	  if (pad >= 0)
	  {
            /* try to consume as many columns as we can, if we don't have
             * memory for that, use as much memory as possible */
            if (wlen + (pad * pl) + len > destlen)
              pad = (destlen > wlen + len) ? ((destlen - wlen - len) / pl) : 0;
            else
            {
              /* Add pre-spacing to make multi-column pad characters and
               * the contents after padding line up */
              while ((col + (pad * pw) + wid < cols) &&
                     (wlen + (pad * pl) + len < destlen))
              {
                *wptr++ = ' ';
                wlen++;
                col++;
              }
            }
	    while (pad-- > 0)
	    {
	      memcpy (wptr, src, pl);
	      wptr += pl;
	      wlen += pl;
	      col += pw;
	    }
	  }
	  else if (soft && pad < 0)
	  {
	    int offset = ((flags & MUTT_FORMAT_ARROWCURSOR) && option (OPTARROWCURSOR)) ? 3 : 0;
            int avail_cols = (cols > offset) ? (cols - offset) : 0;
	    /* \0-terminate dest for length computation in mutt_wstr_trunc() */
	    *wptr = 0;
	    /* make sure right part is at most as wide as display */
	    len = mutt_wstr_trunc (buf, destlen, avail_cols, &wid);
	    /* truncate left so that right part fits completely in */
	    wlen = mutt_wstr_trunc (dest, destlen - len, avail_cols - wid, &col);
	    wptr = dest + wlen;
            /* Multi-column characters may be truncated in the middle.
             * Add spacing so the right hand side lines up. */
            while ((col + wid < avail_cols) && (wlen + len < destlen))
            {
              *wptr++ = ' ';
              wlen++;
              col++;
            }
	  }
	  if (len + wlen > destlen)
	    len = mutt_wstr_trunc (buf, destlen - wlen, cols - col, NULL);
	  memcpy (wptr, buf, len);
	  wptr += len;
	  wlen += len;
	  col += wid;
	  src += pl;
	}
	break; /* skip rest of input */
      }
      else if (ch == '|')
      {
	/* pad to EOL */
	int pl, pw, c;
	if ((pl = mutt_charlen (src, &pw)) <= 0)
	  pl = pw = 1;

	/* see if there's room to add content, else ignore */
	if (col < cols && wlen < destlen)
	{
	  c = (cols - col) / pw;
	  if (c > 0 && wlen + (c * pl) > destlen)
	    c = ((signed)(destlen - wlen)) / pl;
	  while (c > 0)
	  {
	    memcpy (wptr, src, pl);
	    wptr += pl;
	    wlen += pl;
	    col += pw;
	    c--;
	  }
	  src += pl;
	}
	break; /* skip rest of input */
      }
      else
      {
	short tolower =  0;
	short nodots  = 0;
	
	while (ch == '_' || ch == ':') 
	{
	  if (ch == '_')
	    tolower = 1;
	  else if (ch == ':') 
	    nodots = 1;
	  
	  ch = *src++;
	}
	
	/* use callback function to handle this case */
	src = callback (buf, sizeof (buf), col, cols, ch, src, prefix, ifstring, elsestring, data, flags);

	if (tolower)
	  mutt_strlower (buf);
	if (nodots) 
	{
	  char *p = buf;
	  for (; *p; p++)
	    if (*p == '.')
		*p = '_';
	}
	
	if ((len = mutt_strlen (buf)) + wlen > destlen)
	  len = mutt_wstr_trunc (buf, destlen - wlen, cols - col, NULL);

	memcpy (wptr, buf, len);
	wptr += len;
	wlen += len;
	col += mutt_strwidth (buf);
      }
    }
    else if (*src == '\\')
    {
      if (!*++src)
	break;
      switch (*src)
      {
	case 'n':
	  *wptr = '\n';
	  break;
	case 't':
	  *wptr = '\t';
	  break;
	case 'r':
	  *wptr = '\r';
	  break;
	case 'f':
	  *wptr = '\f';
	  break;
	case 'v':
	  *wptr = '\v';
	  break;
	default:
	  *wptr = *src;
	  break;
      }
      src++;
      wptr++;
      wlen++;
      col++;
    }
    else
    {
      int tmp, w;
      /* in case of error, simply copy byte */
      if ((tmp = mutt_charlen (src, &w)) < 0)
	tmp = w = 1;
      if (tmp > 0 && wlen + tmp < destlen)
      {
        memcpy (wptr, src, tmp);
        wptr += tmp;
        src += tmp;
        wlen += tmp;
        col += w;
      }
      else
      {
	src += destlen - wlen;
	wlen = destlen;
      }
    }
  }
  *wptr = 0;

#if 0
  if (flags & MUTT_FORMAT_MAKEPRINT)
  {
    /* Make sure that the string is printable by changing all non-printable
       chars to dots, or spaces for non-printable whitespace */
    for (cp = dest ; *cp ; cp++)
      if (!IsPrint (*cp) &&
	  !((flags & MUTT_FORMAT_TREE) && (*cp <= MUTT_TREE_MAX)))
	*cp = isspace ((unsigned char) *cp) ? ' ' : '.';
  }
#endif
}