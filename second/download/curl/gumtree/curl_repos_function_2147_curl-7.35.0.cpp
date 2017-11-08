int Curl_ssl_init_certinfo(struct SessionHandle * data,
                           int num)
{
  struct curl_certinfo * ci = &data->info.certs;
  struct curl_slist * * table;

  /* Initialize the certificate information structures. Return 0 if OK, else 1.
   */
  Curl_ssl_free_certinfo(data);
  ci->num_of_certs = num;
  table = calloc((size_t) num, sizeof(struct curl_slist *));
  if(!table)
    return 1;

  ci->certinfo = table;
  return 0;
}