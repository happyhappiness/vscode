static int 
_mutt_parse_uncolor (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err, 
			 short parse_uncolor)
{
  int object = 0, do_cache = 0;
  COLOR_LINE *tmp, *last = NULL;

  mutt_extract_token (buf, s, 0);

  if ((object = mutt_getvaluebyname (buf->data, Fields)) == -1)
  {
    snprintf (err->data, err->dsize, _("%s: no such object"), buf->data);
    return (-1);
  }

  if (mutt_strncmp (buf->data, "index", 5) != 0)
  {
    snprintf (err->data, err->dsize,
	      _("%s: command valid only for index object"), 
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
     (parse_uncolor && !option(OPTNOCURSES) && !has_colors())
     || (!parse_uncolor && has_colors())
#else
     parse_uncolor
#endif
     )
  {
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
      for (tmp = ColorIndexList; tmp; )
      {
        if (!do_cache)
	  do_cache = 1;
	last = tmp;
	tmp = tmp->next;
	mutt_free_color_line(&last, parse_uncolor);
      }
      ColorIndexList = NULL;
    }
    else
    {
      for (last = NULL, tmp = ColorIndexList; tmp; last = tmp, tmp = tmp->next)
      {
	if (!mutt_strcmp (buf->data, tmp->pattern))
	{
          if (!do_cache)
	    do_cache = 1;
	  dprint(1,(debugfile,"Freeing pattern \"%s\" from ColorIndexList\n",
	                       tmp->pattern));
	  if (last)
	    last->next = tmp->next;
	  else
	    ColorIndexList = tmp->next;
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
    set_option (OPTFORCEREDRAWINDEX);
    /* force re-caching of index colors */
    for (i = 0; Context && i < Context->msgcount; i++)
      Context->hdrs[i]->pair = 0;
  }
  return (0);
}