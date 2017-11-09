static void update_content_info (CONTENT *info, CONTENT_STATE *s, char *d, size_t dlen)
{
  int from = s->from;
  int whitespace = s->whitespace;
  int dot = s->dot;
  int linelen = s->linelen;
  int was_cr = s->was_cr;

  if (!d) /* This signals EOF */
  {
    if (was_cr)
      info->binary = 1;
    if (linelen > info->linemax)
      info->linemax = linelen;

    return;
  }

  for (; dlen; d++, dlen--)
  {
    char ch = *d;

    if (was_cr)
    {
      was_cr = 0;
      if (ch != '\n')
      {
        info->binary = 1;
      }
      else
      {
        if (whitespace) info->space = 1;
	if (dot) info->dot = 1;
        if (linelen > info->linemax) info->linemax = linelen;
        whitespace = 0;
	dot = 0;
        linelen = 0;
	continue;
      }
    }

    linelen++;
    if (ch == '\n')
    {
      info->crlf++;
      if (whitespace) info->space = 1;
      if (dot) info->dot = 1;
      if (linelen > info->linemax) info->linemax = linelen;
      whitespace = 0;
      linelen = 0;
      dot = 0;
    }
    else if (ch == '\r')
    {
      info->crlf++;
      info->cr = 1;
      was_cr = 1;
      continue;
    }
    else if (ch & 0x80)
      info->hibin++;
    else if (ch == '\t' || ch == '\f')
    {
      info->ascii++;
      whitespace++;
    }
    else if (ch == 0)
    {
      info->nulbin++;
      info->lobin++;
    }
    else if (ch < 32 || ch == 127)
      info->lobin++;
    else
    {
      if (linelen == 1)
      {
        if ((ch == 'F') || (ch == 'f'))
          from = 1;
        else
          from = 0;
        if (ch == '.')
          dot = 1;
        else
          dot = 0;
      }
      else if (from)
      {
        if (linelen == 2 && ch != 'r') from = 0;
        else if (linelen == 3 && ch != 'o') from = 0;
        else if (linelen == 4)
	{
          if (ch == 'm') info->from = 1;
          from = 0;
        }
      }
      if (ch == ' ') whitespace++;
      info->ascii++;
    }

    if (linelen > 1) dot = 0;
    if (ch != ' ' && ch != '\t') whitespace = 0;
  }

  s->from = from;
  s->whitespace = whitespace;
  s->dot = dot;
  s->linelen = linelen;
  s->was_cr = was_cr;

}