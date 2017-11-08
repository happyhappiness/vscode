static const char *
   add_proxy_http_headers(cmd_parms *parms, void *dconf, int flag)
{
   proxy_dir_conf *conf = dconf;
   conf->add_forwarded_headers = flag;
   return NULL;
}