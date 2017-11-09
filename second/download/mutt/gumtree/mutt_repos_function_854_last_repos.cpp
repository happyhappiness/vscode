static int
parse_attr_spec(BUFFER *buf, BUFFER *s, int *fg, int *bg, int *attr, BUFFER *err)
{
  
  if(fg) *fg = -1; 
  if(bg) *bg = -1;

  if (! MoreArgs (s))
  {
    strfcpy (err->data, _("mono: too few arguments"), err->dsize);
    return (-1);
  }

  mutt_extract_token (buf, s, 0);

  if (ascii_strcasecmp ("bold", buf->data) == 0)
    *attr |= A_BOLD;
  else if (ascii_strcasecmp ("underline", buf->data) == 0)
    *attr |= A_UNDERLINE;
  else if (ascii_strcasecmp ("none", buf->data) == 0)
    *attr = A_NORMAL;
  else if (ascii_strcasecmp ("reverse", buf->data) == 0)
    *attr |= A_REVERSE;
  else if (ascii_strcasecmp ("standout", buf->data) == 0)
    *attr |= A_STANDOUT;
  else if (ascii_strcasecmp ("normal", buf->data) == 0)
    *attr = A_NORMAL; /* needs use = instead of |= to clear other bits */
  else
  {
    snprintf (err->data, err->dsize, _("%s: no such attribute"), buf->data);
    return (-1);
  }
  
  return 0;
}