int mutt_parse_unmono (BUFFER *buf, BUFFER *s, unsigned long data,
		       BUFFER *err)
{
  return _mutt_parse_uncolor(buf, s, data, err, 0);
}