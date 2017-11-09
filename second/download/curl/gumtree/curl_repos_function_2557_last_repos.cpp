void Curl_ssl_cleanup(void)
{
  if(init_ssl) {
    /* only cleanup if we did a previous init */
    Curl_ssl->cleanup();
    init_ssl = FALSE;
  }
}