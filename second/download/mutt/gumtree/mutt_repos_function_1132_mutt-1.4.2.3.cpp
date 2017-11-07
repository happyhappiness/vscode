static int parse_source (BUFFER *tmp, BUFFER *s, unsigned long data, BUFFER *err)
{
  char path[_POSIX_PATH_MAX];

  if (mutt_extract_token (tmp, s, 0) != 0)
  {
    snprintf (err->data, err->dsize, _("source: error at %s"), s->dptr);
    return (-1);
  }
  if (MoreArgs (s))
  {
    strfcpy (err->data, _("source: too many arguments"), err->dsize);
    return (-1);
  }
  strfcpy (path, tmp->data, sizeof (path));
  mutt_expand_path (path, sizeof (path));
  return (source_rc (path, err));
}