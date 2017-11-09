static size_t wrfu(void *ptr, size_t size, size_t nmemb, void *stream)
{
  const struct curl_tlssessioninfo *info;
  unsigned int cert_list_size;
  const gnutls_datum_t *chainp;
  CURLcode res;

  (void)stream;
  (void)ptr;

  res = curl_easy_getinfo(curl, CURLINFO_TLS_SESSION, &info);

  if(!res) {
    switch(info->backend) {
    case CURLSSLBACKEND_GNUTLS:
      /* info->internals is now the gnutls_session_t */
      chainp = gnutls_certificate_get_peers(info->internals, &cert_list_size);
      if((chainp) && (cert_list_size)) {
        unsigned int i;

        for(i = 0; i < cert_list_size; i++) {
          gnutls_x509_crt_t cert;
          gnutls_datum_t dn;

          if(GNUTLS_E_SUCCESS == gnutls_x509_crt_init(&cert)) {
            if(GNUTLS_E_SUCCESS ==
               gnutls_x509_crt_import(cert, &chainp[i], GNUTLS_X509_FMT_DER)) {
              if(GNUTLS_E_SUCCESS ==
                 gnutls_x509_crt_print(cert, GNUTLS_CRT_PRINT_FULL, &dn)) {
                fprintf(stderr, "Certificate #%d: %.*s", i, dn.size, dn.data);

                gnutls_free(dn.data);
              }
            }

            gnutls_x509_crt_deinit(cert);
          }
        }
      }
      break;
    case CURLSSLBACKEND_NONE:
    default:
      break;
    }
  }

  return size * nmemb;
}