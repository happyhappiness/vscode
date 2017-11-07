void mutt_decode_quoted (STATE *s, long len, int istext, iconv_t cd)
{
  char line[STRING];
  char decline[2*STRING];
  size_t l = 0;
  size_t l2;
  size_t l3;
  
  int last;
  
  if (istext)
    state_set_prefix(s);

  while (len > 0)
  {
    last = 0;
    
    if (fgets (line, MIN (sizeof (line), len + 1), s->fpin) == NULL)
      break;

    len -= (l2 = strlen (line));

    /* 
     * Skip over pending input data until end of line - at this
     * point, the only thing we may see is trailing whitespace,
     * i.e. garbage.
     */

    if (l2 && (last = line[l2 - 1]) != '\n')
      while (len > 0 && (last = fgetc (s->fpin)) != '\n')
	len--;

    /* 
     * decode and do character set conversion
     */
    
    qp_decode_line (decline + l, line, &l3, last);
    l += l3;
    convert_to_state (cd, decline, &l, s);
  }

  convert_to_state (cd, 0, 0, s);
  state_reset_prefix(s);
}