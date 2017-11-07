int url_parse_mailto (ENVELOPE *e, char **body, const char *src)
{
  char *t;
  char *tmp;
  char *headers;
  char *tag, *value;
  char scratch[HUGE_STRING];

  int taglen;

  LIST *last = NULL;
  
  if (!(t = strchr (src, ':')))
    return -1;
  
  if ((tmp = safe_strdup (t + 1)) == NULL)
    return -1;

  if ((headers = strchr (tmp, '?')))
    *headers++ = '\0';

  url_pct_decode (tmp);
  e->to = rfc822_parse_adrlist (e->to, tmp);

  tag = headers ? strtok (headers, "&") : NULL;
  
  for (; tag; tag = strtok (NULL, "&"))
  {
    if ((value = strchr (tag, '=')))
      *value++ = '\0';
    if (!value || !*value)
      continue;

    url_pct_decode (tag);
    url_pct_decode (value);

    if (!ascii_strcasecmp (tag, "body"))
      mutt_str_replace (body, value);
    else 
    {
      taglen = strlen (tag);
      /* mutt_parse_rfc822_line makes some assumptions */
      snprintf (scratch, sizeof (scratch), "%s: %s", tag, value);
      scratch[taglen] = '\0';
      value = &scratch[taglen+1];
      SKIPWS (value);
      mutt_parse_rfc822_line (e, NULL, scratch, value, 1, 0, 0, &last);
    }
  }
  
  safe_free ((void **) &tmp);
  return 0;
}