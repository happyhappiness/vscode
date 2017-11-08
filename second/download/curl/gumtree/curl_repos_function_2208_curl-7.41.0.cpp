static CURLcode
cyassl_connect_step2(struct connectdata *conn,
                     int sockindex)
{
  int ret = -1;
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data* conssl = &conn->ssl[sockindex];

  infof(data, "CyaSSL: Connecting to %s:%d\n",
        conn->host.name, conn->remote_port);

  conn->recv[sockindex] = cyassl_recv;
  conn->send[sockindex] = cyassl_send;

  /* Enable RFC2818 checks */
  if(data->set.ssl.verifyhost) {
    ret = CyaSSL_check_domain_name(conssl->handle, conn->host.name);
    if(ret == SSL_FAILURE)
      return CURLE_OUT_OF_MEMORY;
  }

  ret = SSL_connect(conssl->handle);
  if(ret != 1) {
    char error_buffer[80];
    int  detail = SSL_get_error(conssl->handle, ret);

    if(SSL_ERROR_WANT_READ == detail) {
      conssl->connecting_state = ssl_connect_2_reading;
      return CURLE_OK;
    }
    else if(SSL_ERROR_WANT_WRITE == detail) {
      conssl->connecting_state = ssl_connect_2_writing;
      return CURLE_OK;
    }
    /* There is no easy way to override only the CN matching.
     * This will enable the override of both mismatching SubjectAltNames
     * as also mismatching CN fields */
    else if(DOMAIN_NAME_MISMATCH == detail) {
#if 1
      failf(data, "\tsubject alt name(s) or common name do not match \"%s\"\n",
            conn->host.dispname);
      return CURLE_PEER_FAILED_VERIFICATION;
#else
      /* When the CyaSSL_check_domain_name() is used and you desire to continue
       * on a DOMAIN_NAME_MISMATCH, i.e. 'data->set.ssl.verifyhost == 0',
       * CyaSSL version 2.4.0 will fail with an INCOMPLETE_DATA error. The only
       * way to do this is currently to switch the CyaSSL_check_domain_name()
       * in and out based on the 'data->set.ssl.verifyhost' value. */
      if(data->set.ssl.verifyhost) {
        failf(data,
              "\tsubject alt name(s) or common name do not match \"%s\"\n",
              conn->host.dispname);
        return CURLE_PEER_FAILED_VERIFICATION;
      }
      else {
        infof(data,
              "\tsubject alt name(s) and/or common name do not match \"%s\"\n",
              conn->host.dispname);
        return CURLE_OK;
      }
#endif
    }
#if LIBCYASSL_VERSION_HEX >= 0x02007000 /* 2.7.0 */
    else if(ASN_NO_SIGNER_E == detail) {
      if(data->set.ssl.verifypeer) {
        failf(data, "\tCA signer not available for verification\n");
        return CURLE_SSL_CACERT_BADFILE;
      }
      else {
        /* Just continue with a warning if no strict certificate
           verification is required. */
        infof(data, "CA signer not available for verification, "
                    "continuing anyway\n");
      }
    }
#endif
    else {
      failf(data, "SSL_connect failed with error %d: %s", detail,
          ERR_error_string(detail, error_buffer));
      return CURLE_SSL_CONNECT_ERROR;
    }
  }

  conssl->connecting_state = ssl_connect_3;
  infof(data, "SSL connected\n");

  return CURLE_OK;
}