static CURLcode getinfo_slist(struct SessionHandle *data, CURLINFO info,
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
    {
      struct curl_tlssessioninfo **tsip = (struct curl_tlssessioninfo **)
                                          param_slistp;
      struct curl_tlssessioninfo *tsi = &data->tsi;
      struct connectdata *conn = data->easy_conn;
      unsigned int sockindex = 0;
      void *internals = NULL;

      *tsip = tsi;
      tsi->backend = CURLSSLBACKEND_NONE;
      tsi->internals = NULL;

      if(!conn)
        break;

      /* Find the active ("in use") SSL connection, if any */
      while((sockindex < sizeof(conn->ssl) / sizeof(conn->ssl[0])) &&
            (!conn->ssl[sockindex].use))
        sockindex++;

      if(sockindex == sizeof(conn->ssl) / sizeof(conn->ssl[0]))
        break; /* no SSL session found */

      /* Return the TLS session information from the relevant backend */
#ifdef USE_SSLEAY
      internals = conn->ssl[sockindex].ctx;
#endif
#ifdef USE_GNUTLS
      internals = conn->ssl[sockindex].session;
#endif
#ifdef USE_NSS
      internals = conn->ssl[sockindex].handle;
#endif
#ifdef USE_GSKIT
      internals = conn->ssl[sockindex].handle;
#endif
      if(internals) {
        tsi->backend = Curl_ssl_backend();
        tsi->internals = internals;
      }
      /* NOTE: For other SSL backends, it is not immediately clear what data
         to return from 'struct ssl_connect_data'; thus, for now we keep the
         backend as CURLSSLBACKEND_NONE in those cases, which should be
         interpreted as "not supported" */
    }
    break;
  default:
    return CURLE_BAD_FUNCTION_ARGUMENT;
  }

  return CURLE_OK;
}