int mutt_parse_color(BUFFER *buff, BUFFER *s, unsigned long data, BUFFER *err)
{
  int dry_run = 0;
  
  if(option(OPTNOCURSES) || !has_colors())
    dry_run = 1;
  
  return _mutt_parse_color(buff, s, err, parse_color_pair, dry_run);
}