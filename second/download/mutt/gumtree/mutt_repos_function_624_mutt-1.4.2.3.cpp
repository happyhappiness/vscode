void mutt_decode_base64 (STATE *s, long len, int istext, iconv_t cd)
{
  char buf[5];
  int c1, c2, c3, c4, ch, cr = 0, i;
  char bufi[BUFI_SIZE];
  size_t l = 0;

  buf[4] = 0;

  if (istext) 
    state_set_prefix(s);

  while (len > 0)
  {
    for (i = 0 ; i < 4 && len > 0 ; len--)
    {
      if ((ch = fgetc (s->fpin)) == EOF)
	return;
      if (!ISSPACE (ch))
	buf[i++] = ch;
    }
    if (i != 4)
    {
      dprint (2, (debugfile, "%s:%d [mutt_decode_base64()]: "
		  "didn't get a multiple of 4 chars.\n", __FILE__, __LINE__));
      break;
    }

    c1 = base64val (buf[0]);
    c2 = base64val (buf[1]);
    ch = (c1 << 2) | (c2 >> 4);

    if (cr && ch != '\n') 
      bufi[l++] = '\r';

    cr = 0;
      
    if (istext && ch == '\r')
      cr = 1;
    else
      bufi[l++] = ch;

    if (buf[2] == '=')
      break;
    c3 = base64val (buf[2]);
    ch = ((c2 & 0xf) << 4) | (c3 >> 2);

    if (cr && ch != '\n')
      bufi[l++] = '\r';

    cr = 0;

    if (istext && ch == '\r')
      cr = 1;
    else
      bufi[l++] = ch;

    if (buf[3] == '=') break;
    c4 = base64val (buf[3]);
    ch = ((c3 & 0x3) << 6) | c4;

    if (cr && ch != '\n')
      bufi[l++] = '\r';
    cr = 0;

    if (istext && ch == '\r')
      cr = 1;
    else
      bufi[l++] = ch;
    
    if (l + 8 >= sizeof (bufi))
      convert_to_state (cd, bufi, &l, s);
  }

  if (cr) bufi[l++] = '\r';

  convert_to_state (cd, bufi, &l, s);
  convert_to_state (cd, 0, 0, s);

  state_reset_prefix(s);
}