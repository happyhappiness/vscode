CURLcode Curl_initinfo(struct SessionHandle *data)
{
  struct Progress *pro = &data->progress;
  struct PureInfo *info =&data->info;

  pro->t_nslookup = 0;
  pro->t_connect = 0;
  pro->t_pretransfer = 0;

  info->httpcode = 0;
  info->httpversion=0;
  info->filetime=0;

  return CURLE_OK;
}