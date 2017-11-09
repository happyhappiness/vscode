static int tls_init (void)
{
  static unsigned char init_complete = 0;
  int err;

  if (init_complete)
    return 0;

  err = gnutls_global_init();
  if (err < 0)
  {
    mutt_error ("gnutls_global_init: %s", gnutls_strerror(err));
    mutt_sleep (2);
    return -1;
  }

  init_complete = 1;
  return 0;
}