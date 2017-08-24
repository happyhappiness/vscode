{
    ret = gnutls_global_init()?0:1;
#ifdef GTLSDEBUG
    gnutls_global_set_log_function(tls_log_func);
    gnutls_global_set_log_level(2);
#endif
    gtls_inited = TRUE;
  }