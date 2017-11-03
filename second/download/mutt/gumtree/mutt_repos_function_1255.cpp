static void encode_headers (LIST *h)
{
  char *tmp;
  char *p;
  int i;

  for (; h; h = h->next)
  {
    if (!(p = strchr (h->data, ':')))
      continue;

    i = p - h->data;
    p = skip_email_wsp(p + 1);
    tmp = safe_strdup (p);

    if (!tmp)
      continue;

    rfc2047_encode_string (&tmp);
    safe_realloc (&h->data, mutt_strlen (h->data) + 2 + mutt_strlen (tmp) + 1);

    sprintf (h->data + i, ": %s", NONULL (tmp));  /* __SPRINTF_CHECKED__ */

    FREE (&tmp);
  }
}