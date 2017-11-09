int url_parse_file (char *d, const char *src, size_t dl)
{
  if (ascii_strncasecmp (src, "file:", 5))
    return -1;
  else if (!ascii_strncasecmp (src, "file://", 7))	/* we don't support remote files */
    return -1;
  else
    strfcpy (d, src + 5, dl);

  return url_pct_decode (d);
}