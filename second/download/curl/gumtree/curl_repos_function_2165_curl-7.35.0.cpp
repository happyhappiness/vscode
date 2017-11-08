static CURLcode cert_stuff(struct connectdata *conn, int sockindex,
                           char *cert_file, char *key_file)
{
  struct SessionHandle *data = conn->data;
  CURLcode rv;

  if(cert_file) {
    rv = nss_load_cert(&conn->ssl[sockindex], cert_file, PR_FALSE);
    if(CURLE_OK != rv) {
      const PRErrorCode err = PR_GetError();
      if(!display_error(conn, err, cert_file)) {
        const char *err_name = nss_error_to_name(err);
        failf(data, "unable to load client cert: %d (%s)", err, err_name);
      }

      return rv;
    }
  }

  if(key_file || (is_file(cert_file))) {
    if(key_file)
      rv = nss_load_key(conn, sockindex, key_file);
    else
      /* In case the cert file also has the key */
      rv = nss_load_key(conn, sockindex, cert_file);
    if(CURLE_OK != rv) {
      const PRErrorCode err = PR_GetError();
      if(!display_error(conn, err, key_file)) {
        const char *err_name = nss_error_to_name(err);
        failf(data, "unable to load client key: %d (%s)", err, err_name);
      }

      return rv;
    }
  }

  return CURLE_OK;
}