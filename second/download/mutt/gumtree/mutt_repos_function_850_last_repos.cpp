static int _mutt_parse_uncolor (BUFFER *buf, BUFFER *s, unsigned long data,
				BUFFER *err, short parse_uncolor)
{
  int object = 0, do_cache = 0;
  COLOR_LINE *tmp, *last = NULL;
  COLOR_LINE **list;

  mutt_extract_token (buf, s, 0);

  if ((object = mutt_getvaluebyname (buf->data, Fields)) == -1)
  {
    snprintf (err->data, err->dsize, _("%s: no such object"), buf->data);
    return (-1);
  }

  if (mutt_strncmp (buf->data, "index", 5) == 0)
    list = &ColorIndexList;
  else if (mutt_strncmp (buf->data, "body", 4) == 0)
    list = &ColorBodyList;
  else if (mutt_strncmp (buf->data, "header", 7) == 0)
    list = &ColorHdrList;
  else
  {
    snprintf (err->data, err->dsize,
	      _("%s: command valid only for index, body, header objects"),
	      parse_uncolor ? "uncolor" : "unmono");
    return (-1);
  }

  if (!MoreArgs (s))
  {
    snprintf (err->data, err->dsize,
	      _("%s: too few arguments"), parse_uncolor ? "uncolor" : "unmono");
    return (-1);
  }

  if(
#ifdef HAVE_COLOR
     /* we're running without curses */
     option (OPTNOCURSES) 
     || /* we're parsing an uncolor command, and have no colors */
     (parse_uncolor && !has_colors())
     /* we're parsing an unmono command, and have colors */
     || (!parse_uncolor && has_colors())
#else
     /* We don't even have colors compiled in */
     parse_uncolor
#endif
     )
  {
    /* just eat the command, but don't do anything real about it */
    do
      mutt_extract_token (buf, s, 0);
    while (MoreArgs (s));

    return 0;
  }

  do
  {
    mutt_extract_token (buf, s, 0);
    if (!mutt_strcmp ("*", buf->data))
    {
      for (tmp = *list; tmp; )
      {
        if (!do_cache)
	  do_cache = 1;
	last = tmp;
	tmp = tmp->next;
	mutt_free_color_line(&last, parse_uncolor);
      }
      *list = NULL;
    }
    else
    {
      for (last = NULL, tmp = *list; tmp; last = tmp, tmp = tmp->next)
      {
	if (!mutt_strcmp (buf->data, tmp->pattern))
	{
          if (!do_cache)
	    do_cache = 1;
	  dprint(1,(debugfile,"Freeing pattern \"%s\" from color list\n",
	                       tmp->pattern));
	  if (last)
	    last->next = tmp->next;
	  else
	    *list = tmp->next;
	  mutt_free_color_line(&tmp, parse_uncolor);
	  break;
	}
      }
    }
  }
  while (MoreArgs (s));


  if (do_cache && !option (OPTNOCURSES))
  {
    int i;
    mutt_set_menu_redraw_full (MENU_MAIN);
    /* force re-caching of index colors */
    for (i = 0; Context && i < Context->msgcount; i++)
      Context->hdrs[i]->pair = 0;
  }
  return (0);
}