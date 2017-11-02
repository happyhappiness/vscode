int Curl_ossl_init(void)
{
#ifdef HAVE_ENGINE_LOAD_BUILTIN_ENGINES
  ENGINE_load_builtin_engines();
#endif

  /* Lets get nice error messages */
  SSL_load_error_strings();

  /* Init the global ciphers and digests */
  if(!SSLeay_add_ssl_algorithms())
    return 0;

  OpenSSL_add_all_algorithms();


  /* OPENSSL_config(NULL); is "strongly recommended" to use but unfortunately
     that function makes an exit() call on wrongly formatted config files
     which makes it hard to use in some situations. OPENSSL_config() itself
     calls CONF_modules_load_file() and we use that instead and we ignore
     its return code! */

  /* CONF_MFLAGS_DEFAULT_SECTION introduced some time between 0.9.8b and
     0.9.8e */
#ifndef CONF_MFLAGS_DEFAULT_SECTION
#define CONF_MFLAGS_DEFAULT_SECTION 0x0
#endif

  CONF_modules_load_file(NULL, NULL,
                         CONF_MFLAGS_DEFAULT_SECTION|
                         CONF_MFLAGS_IGNORE_MISSING_FILE);

  return 1;
}