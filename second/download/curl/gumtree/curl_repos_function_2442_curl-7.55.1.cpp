bool
Curl_clone_primary_ssl_config(struct ssl_primary_config *source,
                              struct ssl_primary_config *dest)
{
  dest->verifyhost = source->verifyhost;
  dest->verifypeer = source->verifypeer;
  dest->version = source->version;
  dest->version_max = source->version_max;

  CLONE_STRING(CAfile);
  CLONE_STRING(CApath);
  CLONE_STRING(cipher_list);
  CLONE_STRING(egdsocket);
  CLONE_STRING(random_file);
  CLONE_STRING(clientcert);

  /* Disable dest sessionid cache if a client cert is used, CVE-2016-5419. */
  dest->sessionid = (dest->clientcert ? false : source->sessionid);
  return TRUE;
}