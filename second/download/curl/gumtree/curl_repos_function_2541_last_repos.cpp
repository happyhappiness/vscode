static CURLcode connect_finish(struct connectdata *conn, int sockindex)
{
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  SSL *ssl = BACKEND->ssl;
  const char *peer_CN;
  uint32_t dns_altname_index;
  const char *dns_altname;
  int8_t found_subject_alt_names = 0;
  int8_t found_subject_alt_name_matching_conn = 0;
  const char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
    conn->host.name;
  const char * const dispname = SSL_IS_PROXY() ?
    conn->http_proxy.host.dispname : conn->host.dispname;

  /* Here, gtls.c gets the peer certificates and fails out depending on
   * settings in "data."  axTLS api doesn't have get cert chain fcn, so omit?
   */

  /* Verify server's certificate */
  if(SSL_CONN_CONFIG(verifypeer)) {
    if(ssl_verify_cert(ssl) != SSL_OK) {
      Curl_axtls_close(conn, sockindex);
      failf(data, "server cert verify failed");
      return CURLE_PEER_FAILED_VERIFICATION;
    }
  }
  else
    infof(data, "\t server certificate verification SKIPPED\n");

  /* Here, gtls.c does issuer verification. axTLS has no straightforward
   * equivalent, so omitting for now.*/

  /* Here, gtls.c does the following
   * 1) x509 hostname checking per RFC2818.  axTLS doesn't support this, but
   *    it seems useful. This is now implemented, by Oscar Koeroo
   * 2) checks cert validity based on time.  axTLS does this in ssl_verify_cert
   * 3) displays a bunch of cert information.  axTLS doesn't support most of
   *    this, but a couple fields are available.
   */

  /* There is no (DNS) Altnames count in the version 1.4.8 API. There is a
     risk of an inifite loop */
  for(dns_altname_index = 0; ; dns_altname_index++) {
    dns_altname = ssl_get_cert_subject_alt_dnsname(ssl, dns_altname_index);
    if(dns_altname == NULL) {
      break;
    }
    found_subject_alt_names = 1;

    infof(data, "\tComparing subject alt name DNS with hostname: %s <-> %s\n",
          dns_altname, hostname);
    if(Curl_cert_hostcheck(dns_altname, hostname)) {
      found_subject_alt_name_matching_conn = 1;
      break;
    }
  }

  /* RFC2818 checks */
  if(found_subject_alt_names && !found_subject_alt_name_matching_conn) {
    if(SSL_CONN_CONFIG(verifyhost)) {
      /* Break connection ! */
      Curl_axtls_close(conn, sockindex);
      failf(data, "\tsubjectAltName(s) do not match %s\n", dispname);
      return CURLE_PEER_FAILED_VERIFICATION;
    }
    else
      infof(data, "\tsubjectAltName(s) do not match %s\n", dispname);
  }
  else if(found_subject_alt_names == 0) {
    /* Per RFC2818, when no Subject Alt Names were available, examine the peer
       CN as a legacy fallback */
    peer_CN = ssl_get_cert_dn(ssl, SSL_X509_CERT_COMMON_NAME);
    if(peer_CN == NULL) {
      if(SSL_CONN_CONFIG(verifyhost)) {
        Curl_axtls_close(conn, sockindex);
        failf(data, "unable to obtain common name from peer certificate");
        return CURLE_PEER_FAILED_VERIFICATION;
      }
      else
        infof(data, "unable to obtain common name from peer certificate");
    }
    else {
      if(!Curl_cert_hostcheck((const char *)peer_CN, hostname)) {
        if(SSL_CONN_CONFIG(verifyhost)) {
          /* Break connection ! */
          Curl_axtls_close(conn, sockindex);
          failf(data, "\tcommon name \"%s\" does not match \"%s\"\n",
                peer_CN, dispname);
          return CURLE_PEER_FAILED_VERIFICATION;
        }
        else
          infof(data, "\tcommon name \"%s\" does not match \"%s\"\n",
                peer_CN, dispname);
      }
    }
  }

  /* General housekeeping */
  connssl->state = ssl_connection_complete;
  conn->recv[sockindex] = axtls_recv;
  conn->send[sockindex] = axtls_send;

  /* Put our freshly minted SSL session in cache */
  if(SSL_SET_OPTION(primary.sessionid)) {
    const uint8_t *ssl_sessionid = ssl_get_session_id(ssl);
    size_t ssl_idsize = ssl_get_session_id_size(ssl);
    Curl_ssl_sessionid_lock(conn);
    if(Curl_ssl_addsessionid(conn, (void *) ssl_sessionid, ssl_idsize,
                             sockindex) != CURLE_OK)
      infof(data, "failed to add session to cache\n");
    Curl_ssl_sessionid_unlock(conn);
  }

  return CURLE_OK;
}