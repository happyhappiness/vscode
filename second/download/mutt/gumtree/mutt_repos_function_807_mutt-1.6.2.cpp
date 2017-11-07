static int
parse_color_pair(BUFFER *buf, BUFFER *s, int *fg, int *bg, int *attr, BUFFER *err)
{
  if (! MoreArgs (s))
  {
    strfcpy (err->data, _("color: too few arguments"), err->dsize);
    return (-1);
  }

  mutt_extract_token (buf, s, 0);

  if (parse_color_name (buf->data, fg, attr, 1, err) != 0)
    return (-1);

  if (! MoreArgs (s))
  {
    strfcpy (err->data, _("color: too few arguments"), err->dsize);
    return (-1);
  }
  
  mutt_extract_token (buf, s, 0);

  if (parse_color_name (buf->data, bg, attr, 0, err) != 0)
    return (-1);
  
  return 0;
}