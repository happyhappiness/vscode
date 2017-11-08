int Curl_nss_seed(struct SessionHandle *data)
{
  /* make sure that NSS is initialized */
  return !!Curl_nss_force_init(data);
}