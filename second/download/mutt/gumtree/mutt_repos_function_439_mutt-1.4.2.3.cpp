int url_ciss_tostring (ciss_url_t* ciss, char* dest, size_t len, int flags)
{
  if (ciss->scheme == U_UNKNOWN)
    return -1;

  snprintf (dest, len, "%s:", mutt_getnamebyvalue (ciss->scheme, UrlMap));

  if (ciss->host)
  {
    strncat (dest, "//", len - strlen (dest));
    if (ciss->user) {
      if (flags & U_DECODE_PASSWD && ciss->pass)
	snprintf (dest + strlen (dest), len - strlen (dest), "%s:%s@",
		  ciss->user, ciss->pass);
      else
	snprintf (dest + strlen (dest), len - strlen (dest), "%s@",
		  ciss->user);
    }

    if (ciss->port)
      snprintf (dest + strlen (dest), len - strlen (dest), "%s:%hu/",
		ciss->host, ciss->port);
    else
      snprintf (dest + strlen (dest), len - strlen (dest), "%s/", ciss->host);
  }

  if (ciss->path)
    strncat (dest, ciss->path, len - strlen (dest));

  return 0;
}