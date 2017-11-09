int url_parse_ciss (ciss_url_t *ciss, char *src)
{
  char *tmp;

  if ((ciss->scheme = url_check_scheme (src)) == U_UNKNOWN)
    return -1;

  tmp = strchr (src, ':') + 1;

  return ciss_parse_userhost (ciss, tmp);
}