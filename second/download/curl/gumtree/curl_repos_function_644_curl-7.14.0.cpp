void Curl_free_ssl_config(struct ssl_config_data* sslc)
{
  if(sslc->CAfile)
    free(sslc->CAfile);

  if(sslc->CApath)
    free(sslc->CApath);

  if(sslc->cipher_list)
    free(sslc->cipher_list);

  if(sslc->egdsocket)
    free(sslc->egdsocket);

  if(sslc->random_file)
    free(sslc->random_file);
}