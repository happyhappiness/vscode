int mutt_parse_uncolor (BUFFER *buf, BUFFER *s, unsigned long data,
			BUFFER *err)
{
  return _mutt_parse_uncolor(buf, s, data, err, 1);
}