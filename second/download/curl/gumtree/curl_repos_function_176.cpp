int conf_init(conf_t *conf)
{
  int i;

  *conf->http_proxy       = 0;
  for (i=0; i<MAX_STRING1; i++)
    conf->proxy_user[i]     = 0;    /* Clean up password from memory */
  *conf->timeserver       = 0;
  return 1;
}