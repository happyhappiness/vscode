static int cert_stuff(struct connectdata *conn, char *cert_file, char *key_file)
{
  struct SessionHandle *data = conn->data;
  int rv = 0;

  if(cert_file) {
    rv = nss_load_cert(cert_file, PR_FALSE);
    if(!rv) {
      if(!display_error(conn, PR_GetError(), cert_file))
        failf(data, "Unable to load client cert %d.", PR_GetError());
      return 0;
    }
  }
  if(key_file || (is_file(cert_file))) {
    if(key_file)
      rv = nss_load_key(conn, key_file);
    else
      /* In case the cert file also has the key */
      rv = nss_load_key(conn, cert_file);
    if(!rv) {
      if(!display_error(conn, PR_GetError(), key_file))
        failf(data, "Unable to load client key %d.", PR_GetError());

      return 0;
    }
  }
  return 1;
}