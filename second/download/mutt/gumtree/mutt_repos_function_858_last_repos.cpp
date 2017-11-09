int mutt_parse_mono(BUFFER *buff, BUFFER *s, unsigned long data, BUFFER *err)
{
  int dry_run = 0;
  
#ifdef HAVE_COLOR
  if(option(OPTNOCURSES) || has_colors())
    dry_run = 1;
#else
  if(option(OPTNOCURSES))
    dry_run = 1;
#endif

  return _mutt_parse_color(buff, s, err, parse_attr_spec, dry_run);
}