static void
resolve_color (struct line_t *lineInfo, int n, int cnt, int flags, int special,
    ansi_attr *a)
{
  int def_color;		/* color without syntax hilight */
  int color;			/* final color */
  static int last_color;	/* last color set */
  int search = 0, i, m;

  if (!cnt)
    last_color = -1;		/* force attrset() */

  if (lineInfo[n].continuation)
  {
    if (!cnt && option (OPTMARKERS))
    {
      SETCOLOR (MT_COLOR_MARKERS);
      addch ('+');
      last_color = ColorDefs[MT_COLOR_MARKERS];
    }
    m = (lineInfo[n].syntax)[0].first;
    cnt += (lineInfo[n].syntax)[0].last;
  }
  else
    m = n;
  if (!(flags & M_SHOWCOLOR))
    def_color = ColorDefs[MT_COLOR_NORMAL];
  else if (lineInfo[m].type == MT_COLOR_HEADER)
    def_color = (lineInfo[m].syntax)[0].color;
  else
    def_color = ColorDefs[lineInfo[m].type];

  if ((flags & M_SHOWCOLOR) && lineInfo[m].type == MT_COLOR_QUOTED)
  {
    struct q_class_t *class = lineInfo[m].quote;

    if (class)
    {
      def_color = class->color;

      while (class && class->length > cnt)
      {
	def_color = class->color;
	class = class->up;
      }
    }
  }

  color = def_color;
  if (flags & M_SHOWCOLOR)
  {
    for (i = 0; i < lineInfo[m].chunks; i++)
    {
      /* we assume the chunks are sorted */
      if (cnt > (lineInfo[m].syntax)[i].last)
	continue;
      if (cnt < (lineInfo[m].syntax)[i].first)
	break;
      if (cnt != (lineInfo[m].syntax)[i].last)
      {
	color = (lineInfo[m].syntax)[i].color;
	break;
      }
      /* don't break here, as cnt might be 
       * in the next chunk as well */
    }
  }

  if (flags & M_SEARCH)
  {
    for (i = 0; i < lineInfo[m].search_cnt; i++)
    {
      if (cnt > (lineInfo[m].search)[i].last)
	continue;
      if (cnt < (lineInfo[m].search)[i].first)
	break;
      if (cnt != (lineInfo[m].search)[i].last)
      {
	color = ColorDefs[MT_COLOR_SEARCH];
	search = 1;
	break;
      }
    }
  }

  /* handle "special" bold & underlined characters */
  if (special || a->attr)
  {
#ifdef HAVE_COLOR
    if ((a->attr & ANSI_COLOR))
    {
      if (a->pair == -1)
	a->pair = mutt_alloc_color (a->fg, a->bg);
      color = a->pair;
      if (a->attr & ANSI_BOLD)
	  color |= A_BOLD;
    }
    else
#endif
      if ((special & A_BOLD) || (a->attr & ANSI_BOLD))
    {
      if (ColorDefs[MT_COLOR_BOLD] && !search)
	color = ColorDefs[MT_COLOR_BOLD];
      else
	color ^= A_BOLD;
    }
    if ((special & A_UNDERLINE) || (a->attr & ANSI_UNDERLINE))
    {
      if (ColorDefs[MT_COLOR_UNDERLINE] && !search)
	color = ColorDefs[MT_COLOR_UNDERLINE];
      else
	color ^= A_UNDERLINE;
    }
    else if (a->attr & ANSI_REVERSE) 
    {
      color ^= A_REVERSE;
    }
    else if (a->attr & ANSI_BLINK) 
    {
      color ^= A_BLINK;
    }
    else if (a->attr & ANSI_OFF)
    {
      a->attr = 0;
    }
  }

  if (color != last_color)
  {
    attrset (color);
    last_color = color;
  }
}