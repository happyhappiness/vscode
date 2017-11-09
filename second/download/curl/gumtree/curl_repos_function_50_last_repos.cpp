int main(void)
{
  CURL *ch;
  CURLcode rv;

  rv = curl_global_init(CURL_GLOBAL_ALL);
  ch = curl_easy_init();
  rv = curl_easy_setopt(ch, CURLOPT_VERBOSE, 0L);
  rv = curl_easy_setopt(ch, CURLOPT_HEADER, 0L);
  rv = curl_easy_setopt(ch, CURLOPT_NOPROGRESS, 1L);
  rv = curl_easy_setopt(ch, CURLOPT_NOSIGNAL, 1L);
  rv = curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, *writefunction);
  rv = curl_easy_setopt(ch, CURLOPT_WRITEDATA, stdout);
  rv = curl_easy_setopt(ch, CURLOPT_HEADERFUNCTION, *writefunction);
  rv = curl_easy_setopt(ch, CURLOPT_HEADERDATA, stderr);
  rv = curl_easy_setopt(ch, CURLOPT_SSLCERTTYPE, "PEM");
  rv = curl_easy_setopt(ch, CURLOPT_SSL_VERIFYPEER, 1L);
  rv = curl_easy_setopt(ch, CURLOPT_URL, "https://www.example.com/");

  /* first try: retrieve page without cacerts' certificate -> will fail
   */
  rv = curl_easy_perform(ch);
  if(rv == CURLE_OK)
    printf("*** transfer succeeded ***\n");
  else
    printf("*** transfer failed ***\n");

  /* second try: retrieve page using cacerts' certificate -> will succeed
   * load the certificate by installing a function doing the necessary
   * "modifications" to the SSL CONTEXT just before link init
   */
  rv = curl_easy_setopt(ch, CURLOPT_SSL_CTX_FUNCTION, *sslctx_function);
  rv = curl_easy_perform(ch);
  if(rv == CURLE_OK)
    printf("*** transfer succeeded ***\n");
  else
    printf("*** transfer failed ***\n");

  curl_easy_cleanup(ch);
  curl_global_cleanup();
  return rv;
}