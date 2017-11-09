static int 
_mutt_parse_color (BUFFER *buf, BUFFER *s, BUFFER *err, 
		   parser_callback_t callback, short dry_run)
{
  int object = 0, attr = 0, fg = 0, bg = 0, q_level = 0;
  int r = 0;

  if(parse_object(buf, s, &object, &q_level, err) == -1)
    return -1;

  if(callback(buf, s, &fg, &bg, &attr, err) == -1)
    return -1;

  /* extract a regular expression if needed */
  
  if (object == MT_COLOR_HEADER || object == MT_COLOR_BODY || object == MT_COLOR_INDEX)
  {
    if (!MoreArgs (s))
    {
      strfcpy (err->data, _("too few arguments"), err->dsize);
      return (-1);
    }

    mutt_extract_token (buf, s, 0);
  }
   
  if (MoreArgs (s))
  {
    strfcpy (err->data, _("too many arguments"), err->dsize);
    return (-1);
  }
  
  /* dry run? */
  
  if(dry_run) return 0;

  
#ifdef HAVE_COLOR
# ifdef HAVE_USE_DEFAULT_COLORS
  if (!option (OPTNOCURSES) && has_colors()
    /* delay use_default_colors() until needed, since it initializes things */
    && (fg == COLOR_DEFAULT || bg == COLOR_DEFAULT)
    && use_default_colors () != OK)
  {
    strfcpy (err->data, _("default colors not supported"), err->dsize);
    return (-1);
  }
# endif /* HAVE_USE_DEFAULT_COLORS */
#endif
  
  if (object == MT_COLOR_HEADER)
    r = add_pattern (&ColorHdrList, buf->data, 0, fg, bg, attr, err,0);
  else if (object == MT_COLOR_BODY)
    r = add_pattern (&ColorBodyList, buf->data, 1, fg, bg, attr, err, 0);
  else if (object == MT_COLOR_INDEX)
  {
    r = add_pattern (&ColorIndexList, buf->data, 1, fg, bg, attr, err, 1);
    mutt_set_menu_redraw_full (MENU_MAIN);
  }
  else if (object == MT_COLOR_QUOTED)
  {
    if (q_level >= ColorQuoteSize)
    {
      safe_realloc (&ColorQuote, (ColorQuoteSize += 2) * sizeof (int));
      ColorQuote[ColorQuoteSize-2] = ColorDefs[MT_COLOR_QUOTED];
      ColorQuote[ColorQuoteSize-1] = ColorDefs[MT_COLOR_QUOTED];
    }
    if (q_level >= ColorQuoteUsed)
      ColorQuoteUsed = q_level + 1;
    if (q_level == 0)
    {
      ColorDefs[MT_COLOR_QUOTED] = fgbgattr_to_color(fg, bg, attr);
      
      ColorQuote[0] = ColorDefs[MT_COLOR_QUOTED];
      for (q_level = 1; q_level < ColorQuoteUsed; q_level++)
      {
	if (ColorQuote[q_level] == A_NORMAL)
	  ColorQuote[q_level] = ColorDefs[MT_COLOR_QUOTED];
      }
    }
    else
      ColorQuote[q_level] = fgbgattr_to_color(fg, bg, attr);
  }
  else
    ColorDefs[object] = fgbgattr_to_color(fg, bg, attr);

  return (r);
}