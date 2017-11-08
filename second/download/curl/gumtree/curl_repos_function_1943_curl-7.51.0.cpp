static CURLcode getinfo_slist(struct Curl_easy *data, CURLINFO info,
                              struct curl_slist **param_slistp)
{
  union {
    struct curl_certinfo *to_certinfo;
    struct curl_slist    *to_slist;
  } ptr;

  switch(info) {
  case CURLINFO_SSL_ENGINES:
    *param_slistp = Curl_ssl_engines_list(data);
    break;
  case CURLINFO_COOKIELIST:
    *param_slistp = Curl_cookie_list(data);
    break;
  case CURLINFO_CERTINFO:
    /* Return the a pointer to the certinfo struct. Not really an slist
       pointer but we can pretend it is here */
    ptr.to_certinfo = &data->info.certs;
    *param_slistp = ptr.to_slist;
    break;
  case CURLINFO_TLS_SESSION:
  case CURLINFO_TLS_SSL_PTR:
    {
      struct curl_tlssessioninfo **tsip = (struct curl_tlssessioninfo **)
                                          param_slistp;
      struct curl_tlssessioninfo *tsi = &data->tsi;
      struct connectdata *conn = data->easy_conn;

      *tsip = tsi;
      tsi->backend = Curl_ssl_backend();
      tsi->internals = NULL;

      if(conn && tsi->backend != CURLSSLBACKEND_NONE) {
        unsigned int i;
        for(i = 0; i < (sizeof(conn->ssl) / sizeof(conn->ssl[0])); ++i) {
          if(conn->ssl[i].use) {
#if defined(USE_AXTLS)
            tsi->internals = (void *)conn->ssl[i].ssl;
#elif defined(USE_CYASSL)
            tsi->internals = (void *)conn->ssl[i].handle;
#elif defined(USE_DARWINSSL)
            tsi->internals = (void *)conn->ssl[i].ssl_ctx;
#elif defined(USE_GNUTLS)
            tsi->internals = (void *)conn->ssl[i].session;
#elif defined(USE_GSKIT)
            tsi->internals = (void *)conn->ssl[i].handle;
#elif defined(USE_MBEDTLS)
            tsi->internals = (void *)&conn->ssl[i].ssl;
#elif defined(USE_NSS)
            tsi->internals = (void *)conn->ssl[i].handle;
#elif defined(USE_OPENSSL)
            /* Legacy: CURLINFO_TLS_SESSION must return an SSL_CTX pointer. */
            tsi->internals = ((info == CURLINFO_TLS_SESSION) ?
                              (void *)conn->ssl[i].ctx :
                              (void *)conn->ssl[i].handle);
#elif defined(USE_POLARSSL)
            tsi->internals = (void *)&conn->ssl[i].ssl;
#elif defined(USE_SCHANNEL)
            tsi->internals = (void *)&conn->ssl[i].ctxt->ctxt_handle;
#elif defined(USE_SSL)
#error "SSL backend specific information missing for CURLINFO_TLS_SSL_PTR"
#endif
            break;
          }
        }
      }
    }
    break;
  default:
    return CURLE_UNKNOWN_OPTION;
  }

  return CURLE_OK;
}