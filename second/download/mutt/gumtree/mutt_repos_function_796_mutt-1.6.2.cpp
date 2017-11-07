static void mutt_free_color_line(COLOR_LINE **l, 
				 int free_colors)
{
  COLOR_LINE *tmp;
 
  if(!l || !*l)
    return;

  tmp = *l;

#ifdef HAVE_COLOR
  if(free_colors && tmp->fg != -1 && tmp->bg != -1)
    mutt_free_color(tmp->fg, tmp->bg);
#endif

  /* we should really introduce a container
   * type for regular expressions.
   */
  
  regfree(&tmp->rx);
  mutt_pattern_free(&tmp->color_pattern);
  FREE (&tmp->pattern);
  FREE (l);		/* __FREE_CHECKED__ */
}