static COLOR_LINE *mutt_new_color_line (void)
{
  COLOR_LINE *p = safe_calloc (1, sizeof (COLOR_LINE));

  p->fg = p->bg = -1;
  
  return (p);
}