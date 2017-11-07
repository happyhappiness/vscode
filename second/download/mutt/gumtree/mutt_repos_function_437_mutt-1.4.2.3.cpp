static char *ciss_parse_userhost (ciss_url_t *ciss, char *src)
{
  char *t;
  char *p;
  char *path;

  ciss->user = NULL;
  ciss->pass = NULL;
  ciss->host = NULL;
  ciss->port = 0;

  if (strncmp (src, "//", 2))
    return src;
  
  src += 2;

  if ((path = strchr (src, '/')))
    *path++ = '\0';
  
  if ((t = strrchr (src, '@')))
  {
    *t = '\0';
    if ((p = strchr (src, ':')))
    {
      *p = '\0';
      ciss->pass = p + 1;
      url_pct_decode (ciss->pass);
    }
    ciss->user = src;
    url_pct_decode (ciss->user);
    t++;
  }
  else
    t = src;
  
  if ((p = strchr (t, ':')))
  {
    *p++ = '\0';
    ciss->port = atoi (p);
  }
  else
    ciss->port = 0;
  
  ciss->host = t;
  url_pct_decode (ciss->host);
  return path;
}