static int grok_ansi(unsigned char *buf, int pos, ansi_attr *a)
{
  int x = pos;

  while (isdigit(buf[x]) || buf[x] == ';')
    x++;

  /* Character Attributes */
  if (option (OPTALLOWANSI) && a != NULL && buf[x] == 'm')
  {
    if (pos == x)
    {
#ifdef HAVE_COLOR
      if (a->pair != -1)
	mutt_free_color (a->fg, a->bg);
#endif
      a->attr = ANSI_OFF;
      a->pair = -1;
    }
    while (pos < x)
    {
      if (buf[pos] == '1' && (pos+1 == x || buf[pos+1] == ';'))
      {
	a->attr |= ANSI_BOLD;
	pos += 2;
      } 
      else if (buf[pos] == '4' && (pos+1 == x || buf[pos+1] == ';'))
      {
	a->attr |= ANSI_UNDERLINE;
	pos += 2;
      }
      else if (buf[pos] == '5' && (pos+1 == x || buf[pos+1] == ';'))
      {
	a->attr |= ANSI_BLINK;
	pos += 2;
      }
      else if (buf[pos] == '7' && (pos+1 == x || buf[pos+1] == ';'))
      {
	a->attr |= ANSI_REVERSE;
	pos += 2;
      }
      else if (buf[pos] == '0' && (pos+1 == x || buf[pos+1] == ';'))
      {
#ifdef HAVE_COLOR
	if (a->pair != -1)
	  mutt_free_color(a->fg,a->bg);
#endif
	a->attr = ANSI_OFF;
	a->pair = -1;
	pos += 2;
      }
      else if (buf[pos] == '3' && isdigit(buf[pos+1]))
      {
#ifdef HAVE_COLOR
	if (a->pair != -1)
	  mutt_free_color(a->fg,a->bg);
#endif
	a->pair = -1;
	a->attr |= ANSI_COLOR;
	a->fg = buf[pos+1] - '0';
	pos += 3;
      }
      else if (buf[pos] == '4' && isdigit(buf[pos+1]))
      {
#ifdef HAVE_COLOR
	if (a->pair != -1)
	  mutt_free_color(a->fg,a->bg);
#endif
	a->pair = -1;
	a->attr |= ANSI_COLOR;
	a->bg = buf[pos+1] - '0';
	pos += 3;
      }
      else 
      {
	while (pos < x && buf[pos] != ';') pos++;
	pos++;
      }
    }
  }
  pos = x;
  return pos;
}