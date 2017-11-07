int url_parse_mailto (ENVELOPE *e, char **body, const char *src)
{
  char *t, *p;
  char *tmp;
  char *headers;
  char *tag, *value;

  int rc = -1;

  LIST *last = NULL;

  if (!(t = strchr (src, ':')))
    return -1;

  /* copy string for safe use of strtok() */
  if ((tmp = safe_strdup (t + 1)) == NULL)
    return -1;

  if ((headers = strchr (tmp, '?')))
    *headers++ = '\0';

  if (url_pct_decode (tmp) < 0)
    goto out;

  e->to = rfc822_parse_adrlist (e->to, tmp);

  tag = headers ? strtok_r (headers, "&", &p) : NULL;

  for (; tag; tag = strtok_r (NULL, "&", &p))
  {
    if ((value = strchr (tag, '=')))
      *value++ = '\0';
    if (!value || !*value)
      continue;

    if (url_pct_decode (tag) < 0)
      goto out;
    if (url_pct_decode (value) < 0)
      goto out;

    /* Determine if this header field is on the allowed list.  Since Mutt
     * interprets some header fields specially (such as
     * "Attach: ~/.gnupg/secring.gpg"), care must be taken to ensure that
     * only safe fields are allowed.
     *
     * RFC2368, "4. Unsafe headers"
     * The user agent interpreting a mailto URL SHOULD choose not to create
     * a message if any of the headers are considered dangerous; it may also
     * choose to create a message with only a subset of the headers given in
     * the URL.
     */
    if (mutt_matches_ignore(tag, MailtoAllow))
    {
      if (!ascii_strcasecmp (tag, "body"))
      {
	if (body)
	  mutt_str_replace (body, value);
      }
      else
      {
	char *scratch;
	size_t taglen = mutt_strlen (tag);

	safe_asprintf (&scratch, "%s: %s", tag, value);
	scratch[taglen] = 0; /* overwrite the colon as mutt_parse_rfc822_line expects */
	value = skip_email_wsp(&scratch[taglen + 1]);
	mutt_parse_rfc822_line (e, NULL, scratch, value, 1, 0, 0, &last);
	FREE (&scratch);
      }
    }
  }

  rc = 0;

out:
  FREE (&tmp);
  return rc;
}