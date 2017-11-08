bool
Curl_clone_ssl_config(struct ssl_config_data *source,
                      struct ssl_config_data *dest)
{
  dest->verifyhost = source->verifyhost;
  dest->verifypeer = source->verifypeer;
  dest->version = source->version;

  if(source->CAfile) {
    dest->CAfile = strdup(source->CAfile);
    if(!dest->CAfile)
      return FALSE;
  }

  if(source->CApath) {
    dest->CApath = strdup(source->CApath);
    if(!dest->CApath)
      return FALSE;
  }

  if(source->cipher_list) {
    dest->cipher_list = strdup(source->cipher_list);
    if(!dest->cipher_list)
      return FALSE;
  }

  if(source->egdsocket) {
    dest->egdsocket = strdup(source->egdsocket);
    if(!dest->egdsocket)
      return FALSE;
  }

  if(source->random_file) {
    dest->random_file = strdup(source->random_file);
    if(!dest->random_file)
      return FALSE;
  }

  return TRUE;
}