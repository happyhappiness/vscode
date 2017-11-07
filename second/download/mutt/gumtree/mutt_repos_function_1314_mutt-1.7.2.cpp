static void print_enriched_string (int attr, unsigned char *s, int do_color)
{
  wchar_t wc;
  size_t k;
  size_t n = mutt_strlen ((char *)s);
  mbstate_t mbstate;

  memset (&mbstate, 0, sizeof (mbstate));
  while (*s)
  {
    if (*s < MUTT_TREE_MAX)
    {
      if (do_color)
	SETCOLOR (MT_COLOR_TREE);
      while (*s && *s < MUTT_TREE_MAX)
      {
	switch (*s)
	{
	  case MUTT_TREE_LLCORNER:
	    if (option (OPTASCIICHARS))
	      addch ('`');
#ifdef WACS_LLCORNER
	    else
	      add_wch(WACS_LLCORNER);
#else
	    else if (Charset_is_utf8)
	      addstr ("\342\224\224"); /* WACS_LLCORNER */
	    else
	      addch (ACS_LLCORNER);
#endif
	    break;
	  case MUTT_TREE_ULCORNER:
	    if (option (OPTASCIICHARS))
	      addch (',');
#ifdef WACS_ULCORNER
	    else
	      add_wch(WACS_ULCORNER);
#else
	    else if (Charset_is_utf8)
	      addstr ("\342\224\214"); /* WACS_ULCORNER */
	    else
	      addch (ACS_ULCORNER);
#endif
	    break;
	  case MUTT_TREE_LTEE:
	    if (option (OPTASCIICHARS))
	      addch ('|');
#ifdef WACS_LTEE
	    else
	      add_wch(WACS_LTEE);
#else
	    else if (Charset_is_utf8)
	      addstr ("\342\224\234"); /* WACS_LTEE */
	    else
	      addch (ACS_LTEE);
#endif
	    break;
	  case MUTT_TREE_HLINE:
	    if (option (OPTASCIICHARS))
	      addch ('-');
#ifdef WACS_HLINE
	    else
	      add_wch(WACS_HLINE);
#else
	    else if (Charset_is_utf8)
	      addstr ("\342\224\200"); /* WACS_HLINE */
	    else
	      addch (ACS_HLINE);
#endif
	    break;
	  case MUTT_TREE_VLINE:
	    if (option (OPTASCIICHARS))
	      addch ('|');
#ifdef WACS_VLINE
	    else
	      add_wch(WACS_VLINE);
#else
	    else if (Charset_is_utf8)
	      addstr ("\342\224\202"); /* WACS_VLINE */
	    else
	      addch (ACS_VLINE);
#endif
	    break;
	  case MUTT_TREE_TTEE:
	    if (option (OPTASCIICHARS))
	      addch ('-');
#ifdef WACS_TTEE
	    else
	      add_wch(WACS_TTEE);
#else
	    else if (Charset_is_utf8)
	      addstr ("\342\224\254"); /* WACS_TTEE */
	    else
	      addch (ACS_TTEE);
#endif
	    break;
	  case MUTT_TREE_BTEE:
	    if (option (OPTASCIICHARS))
	      addch ('-');
#ifdef WACS_BTEE
	    else
	      add_wch(WACS_BTEE);
#else
	    else if (Charset_is_utf8)
	      addstr ("\342\224\264"); /* WACS_BTEE */
	    else
	      addch (ACS_BTEE);
#endif
	    break;
	  case MUTT_TREE_SPACE:
	    addch (' ');
	    break;
	  case MUTT_TREE_RARROW:
	    addch ('>');
	    break;
	  case MUTT_TREE_STAR:
	    addch ('*'); /* fake thread indicator */
	    break;
	  case MUTT_TREE_HIDDEN:
	    addch ('&');
	    break;
	  case MUTT_TREE_EQUALS:
	    addch ('=');
	    break;
	  case MUTT_TREE_MISSING:
	    addch ('?');
	    break;
	}
	s++, n--;
      }
      if (do_color) ATTRSET(attr);
    }
    else if ((k = mbrtowc (&wc, (char *)s, n, &mbstate)) > 0)
    {
      addnstr ((char *)s, k);
      s += k, n-= k;
    }
    else
      break;
  }
}