static int Curl_ossl_init(void)
{
#ifdef ENABLE_SSLKEYLOGFILE
  const char *keylog_file_name;
#endif

  OPENSSL_load_builtin_modules();

#ifdef HAVE_ENGINE_LOAD_BUILTIN_ENGINES
  ENGINE_load_builtin_engines();
#endif

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

#if (OPENSSL_VERSION_NUMBER >= 0x10100000L) && \
    !defined(LIBRESSL_VERSION_NUMBER)
  /* OpenSSL 1.1.0+ takes care of initialization itself */
#else
  /* Lets get nice error messages */
  SSL_load_error_strings();

  /* Init the global ciphers and digests */
  if(!SSLeay_add_ssl_algorithms())
    return 0;

  OpenSSL_add_all_algorithms();
#endif

#ifdef ENABLE_SSLKEYLOGFILE
  keylog_file_name = curl_getenv("SSLKEYLOGFILE");
  if(keylog_file_name && !keylog_file_fp) {
    keylog_file_fp = fopen(keylog_file_name, FOPEN_APPENDTEXT);
    if(keylog_file_fp) {
      if(setvbuf(keylog_file_fp, NULL, _IOLBF, 4096)) {
        fclose(keylog_file_fp);
        keylog_file_fp = NULL;
      }
    }
  }
#endif

  return 1;
}