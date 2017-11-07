static int ciss_parse_userhost (ciss_url_t *ciss, char *src)
{
  char *t, *p;

  ciss->user = NULL;
  ciss->pass = NULL;
  ciss->host = NULL;
  ciss->port = 0;

  if (strncmp (src, "//", 2) != 0)
  {
    ciss->path = src;
    return url_pct_decode (ciss->path);
  }

  src += 2;

  if ((ciss->path = strchr (src, '/')))
    *ciss->path++ = '\0';

  if ((t = strrchr (src, '@')))
  {
    *t = '\0';
    if ((p = strchr (src, ':')))
    {
      *p = '\0';
      ciss->pass = p + 1;
      if (url_pct_decode (ciss->pass) < 0)
	return -1;
    }
    ciss->user = src;
    if (url_pct_decode (ciss->user) < 0)
      return -1;
    t++;
  }
  else
    t = src;

  if ((p = strchr (t, ':')))
  {
    int t;
    *p++ = '\0';
    if (mutt_atoi (p, &t) < 0 || t < 0 || t > 0xffff)
      return -1;
    ciss->port = (unsigned short)t;
  }
  else
    ciss->port = 0;

  ciss->host = t;
  return url_pct_decode (ciss->host) >= 0 &&
    (!ciss->path || url_pct_decode (ciss->path) >= 0) ? 0 : -1;
}