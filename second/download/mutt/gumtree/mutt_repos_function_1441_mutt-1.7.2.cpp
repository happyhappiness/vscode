static int
fill_buffer (FILE *f, LOFF_T *last_pos, LOFF_T offset, unsigned char **buf,
	     unsigned char **fmt, size_t *blen, int *buf_ready)
{
  unsigned char *p, *q;
  static int b_read;
  int l;

  if (*buf_ready == 0)
  {
    if (offset != *last_pos)
      fseeko (f, offset, 0);
    if ((*buf = (unsigned char *) mutt_read_line ((char *) *buf, blen, f, &l, MUTT_EOL)) == NULL)
    {
      fmt[0] = 0;
      return (-1);
    }
    *last_pos = ftello (f);
    b_read = (int) (*last_pos - offset);
    *buf_ready = 1;

    safe_realloc (fmt, *blen);

    /* incomplete mbyte characters trigger a segfault in regex processing for
     * certain versions of glibc. Trim them if necessary. */
    if (b_read == *blen - 2)
      b_read -= trim_incomplete_mbyte(*buf, b_read);
    
    /* copy "buf" to "fmt", but without bold and underline controls */
    p = *buf;
    q = *fmt;
    while (*p)
    {
      if (*p == '\010' && (p > *buf))
      {
	if (*(p+1) == '_')	/* underline */
	  p += 2;
	else if (*(p+1) && q > *fmt)	/* bold or overstrike */
	{
	  *(q-1) = *(p+1);
	  p += 2;
	}
	else			/* ^H */
	  *q++ = *p++;
      }
      else if (*p == '\033' && *(p+1) == '[' && is_ansi (p + 2))
      {
	while (*p++ != 'm')	/* skip ANSI sequence */
	  ;
      }
      else if (*p == '\033' && *(p+1) == ']' && check_attachment_marker ((char *) p) == 0)
      {
	dprint (2, (debugfile, "fill_buffer: Seen attachment marker.\n"));
	while (*p++ != '\a')	/* skip pseudo-ANSI sequence */
	  ;
      }
      else
	*q++ = *p++;
    }
    *q = 0;
  }
  return b_read;
}