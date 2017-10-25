int Curl_gtls_init(void)
{
  gnutls_global_init();
#ifdef GTLSDEBUG
  gnutls_global_set_log_function(tls_log_func);
  gnutls_global_set_log_level(2);
#endif
  return 1;
}