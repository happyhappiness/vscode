static int
fill_buffer (FILE *f, long *last_pos, long offset, unsigned char *buf, 
	     unsigned char *fmt, size_t blen, int *buf_ready)
{
  unsigned char *p;
  static int b_read;

  if (*buf_ready == 0)
  {
    buf[blen - 1] = 0;
    if (offset != *last_pos)
      fseek (f, offset, 0);
    if (fgets ((char *) buf, blen - 1, f) == NULL)
    {
      fmt[0] = 0;
      return (-1);
    }
    *last_pos = ftell (f);
    b_read = (int) (*last_pos - offset);
    *buf_ready = 1;

    /* copy "buf" to "fmt", but without bold and underline controls */
    p = buf;
    while (*p)
    {
      if (*p == '\010' && (p > buf))
      {
	if (*(p+1) == '_')	/* underline */
	  p += 2;
	else if (*(p+1))	/* bold or overstrike */
	{
	  *(fmt-1) = *(p+1);
	  p += 2;
	}
	else			/* ^H */
	  *fmt++ = *p++;
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
	*fmt++ = *p++;
    }
    *fmt = 0;
  }
  return b_read;
}