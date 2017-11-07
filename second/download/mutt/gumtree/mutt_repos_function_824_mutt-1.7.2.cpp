static int 
add_pattern (COLOR_LINE **top, const char *s, int sensitive,
	     int fg, int bg, int attr, BUFFER *err,
	     int is_index)
{

  /* is_index used to store compiled pattern
   * only for `index' color object 
   * when called from mutt_parse_color() */

  COLOR_LINE *tmp = *top;

  while (tmp)
  {
    if (sensitive)
    {
      if (mutt_strcmp (s, tmp->pattern) == 0)
	break;
    }
    else
    {
      if (mutt_strcasecmp (s, tmp->pattern) == 0)
	break;
    }
    tmp = tmp->next;
  }

  if (tmp)
  {
#ifdef HAVE_COLOR
    if (fg != -1 && bg != -1)
    {
      if (tmp->fg != fg || tmp->bg != bg)
      {
	mutt_free_color (tmp->fg, tmp->bg);
	tmp->fg = fg;
	tmp->bg = bg;
	attr |= mutt_alloc_color (fg, bg);
      }
      else
	attr |= (tmp->pair & ~A_BOLD);
    }
#endif /* HAVE_COLOR */
    tmp->pair = attr;
  }
  else
  {
    int r;
    char buf[LONG_STRING];

    tmp = mutt_new_color_line ();
    if (is_index) 
    {
      int i;

      strfcpy(buf, NONULL(s), sizeof(buf));
      mutt_check_simple (buf, sizeof (buf), NONULL(SimpleSearch));
      if((tmp->color_pattern = mutt_pattern_comp (buf, MUTT_FULL_MSG, err)) == NULL)
      {
	mutt_free_color_line(&tmp, 1);
	return -1;
      }
      /* force re-caching of index colors */
      for (i = 0; Context && i < Context->msgcount; i++)
	Context->hdrs[i]->pair = 0;
    }
    else if ((r = REGCOMP (&tmp->rx, s, (sensitive ? mutt_which_case (s) : REG_ICASE))) != 0)
    {
      regerror (r, &tmp->rx, err->data, err->dsize);
      mutt_free_color_line(&tmp, 1);
      return (-1);
    }
    tmp->next = *top;
    tmp->pattern = safe_strdup (s);
#ifdef HAVE_COLOR
    if(fg != -1 && bg != -1)
    {
      tmp->fg = fg;
      tmp->bg = bg;
      attr |= mutt_alloc_color (fg, bg);
    }
#endif
    tmp->pair = attr;
    *top = tmp;
  }

  return 0;
}