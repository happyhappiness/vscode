static CURLcode nss_init(struct SessionHandle *data)
{
  char *cert_dir;
  struct_stat st;
  CURLcode rv;

  if(initialized)
    return CURLE_OK;

  /* First we check if $SSL_DIR points to a valid dir */
  cert_dir = getenv("SSL_DIR");
  if(cert_dir) {
    if((stat(cert_dir, &st) != 0) ||
        (!S_ISDIR(st.st_mode))) {
      cert_dir = NULL;
    }
  }

  /* Now we check if the default location is a valid dir */
  if(!cert_dir) {
    if((stat(SSL_DIR, &st) == 0) &&
        (S_ISDIR(st.st_mode))) {
      cert_dir = (char *)SSL_DIR;
    }
  }

  rv = nss_init_core(data, cert_dir);
  if(rv)
    return rv;

  if(num_enabled_ciphers() == 0)
    NSS_SetDomesticPolicy();

  initialized = 1;
  return CURLE_OK;
}