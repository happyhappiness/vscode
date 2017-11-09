int url_ciss_tostring (ciss_url_t* ciss, char* dest, size_t len, int flags)
{
  long l;

  if (ciss->scheme == U_UNKNOWN)
    return -1;

  snprintf (dest, len, "%s:", mutt_getnamebyvalue (ciss->scheme, UrlMap));

  if (ciss->host)
  {
    if (!(flags & U_PATH))
      safe_strcat (dest, len, "//");
    len -= (l = strlen (dest)); dest += l;

    if (ciss->user)
    {
      char u[STRING];
      url_pct_encode (u, sizeof (u), ciss->user);

      if (flags & U_DECODE_PASSWD && ciss->pass)
      {
	char p[STRING];
	url_pct_encode (p, sizeof (p), ciss->pass);
	snprintf (dest, len, "%s:%s@", u, p);
      }
      else
	snprintf (dest, len, "%s@", u);

      len -= (l = strlen (dest)); dest += l;
    }

    if (strchr (ciss->host, ':'))
      snprintf (dest, len, "[%s]", ciss->host);
    else
      snprintf (dest, len, "%s", ciss->host);

    len -= (l = strlen (dest)); dest += l;

    if (ciss->port)
      snprintf (dest, len, ":%hu/", ciss->port);
    else
      snprintf (dest, len, "/");
  }

  if (ciss->path)
    safe_strcat (dest, len, ciss->path);

  return 0;
}