static CURLcode
polarssl_connect_step2(struct connectdata *conn,
                     int sockindex)
{
  int ret;
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data* connssl = &conn->ssl[sockindex];
  char buffer[1024];

#ifdef HAS_ALPN
  const char* next_protocol;
#endif

  char errorbuf[128];
  errorbuf[0] = 0;

  conn->recv[sockindex] = polarssl_recv;
  conn->send[sockindex] = polarssl_send;

  for(;;) {
    if(!(ret = ssl_handshake(&connssl->ssl)))
      break;
    else if(ret != POLARSSL_ERR_NET_WANT_READ &&
            ret != POLARSSL_ERR_NET_WANT_WRITE) {
#ifdef POLARSSL_ERROR_C
     error_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* POLARSSL_ERROR_C */
     failf(data, "ssl_handshake returned - PolarSSL: (-0x%04X) %s",
                                                    -ret, errorbuf);

     return CURLE_SSL_CONNECT_ERROR;
    }
    else {
      if(ret == POLARSSL_ERR_NET_WANT_READ) {
        connssl->connecting_state = ssl_connect_2_reading;
        return CURLE_OK;
      }
      if(ret == POLARSSL_ERR_NET_WANT_WRITE) {
        connssl->connecting_state = ssl_connect_2_writing;
        return CURLE_OK;
      }
      failf(data, "SSL_connect failed with error %d.", ret);
      return CURLE_SSL_CONNECT_ERROR;

    }
  }

  infof(data, "PolarSSL: Handshake complete, cipher is %s\n",
        ssl_get_ciphersuite(&conn->ssl[sockindex].ssl)
    );

  ret = ssl_get_verify_result(&conn->ssl[sockindex].ssl);

  if(ret && data->set.ssl.verifypeer) {
    if(ret & BADCERT_EXPIRED)
      failf(data, "Cert verify failed: BADCERT_EXPIRED");

    if(ret & BADCERT_REVOKED) {
      failf(data, "Cert verify failed: BADCERT_REVOKED");
      return CURLE_SSL_CACERT;
    }

    if(ret & BADCERT_CN_MISMATCH)
      failf(data, "Cert verify failed: BADCERT_CN_MISMATCH");

    if(ret & BADCERT_NOT_TRUSTED)
      failf(data, "Cert verify failed: BADCERT_NOT_TRUSTED");

    return CURLE_PEER_FAILED_VERIFICATION;
  }

  if(ssl_get_peer_cert(&(connssl->ssl))) {
    /* If the session was resumed, there will be no peer certs */
    memset(buffer, 0, sizeof(buffer));

    if(x509_crt_info(buffer, sizeof(buffer), (char *)"* ",
                     ssl_get_peer_cert(&(connssl->ssl))) != -1)
      infof(data, "Dumping cert info:\n%s\n", buffer);
  }

#ifdef HAS_ALPN
  if(data->set.ssl_enable_alpn) {
    next_protocol = ssl_get_alpn_protocol(&connssl->ssl);

    if(next_protocol != NULL) {
      infof(data, "ALPN, server accepted to use %s\n", next_protocol);

      if(!strncmp(next_protocol, NGHTTP2_PROTO_VERSION_ID,
                  NGHTTP2_PROTO_VERSION_ID_LEN)) {
        conn->negnpn = NPN_HTTP2;
      }
      else if(!strncmp(next_protocol, ALPN_HTTP_1_1, ALPN_HTTP_1_1_LENGTH)) {
        conn->negnpn = NPN_HTTP1_1;
      }
    }
    else if(connssl->asked_for_h2) {
      infof(data, "ALPN, server did not agree to a protocol\n");
    }
  }
#endif

  connssl->connecting_state = ssl_connect_3;
  infof(data, "SSL connected\n");

  return CURLE_OK;
}