static int ldap_win_bind(struct connectdata *conn, LDAP *server,
                         const char *user, const char *passwd)
{
  int rc = LDAP_INVALID_CREDENTIALS;

  PTCHAR inuser = NULL;
  PTCHAR inpass = NULL;

  if(user && passwd && (conn->data->set.httpauth & CURLAUTH_BASIC)) {
    inuser = Curl_convert_UTF8_to_tchar((char *) user);
    inpass = Curl_convert_UTF8_to_tchar((char *) passwd);

    rc = ldap_simple_bind_s(server, inuser, inpass);

    Curl_unicodefree(inuser);
    Curl_unicodefree(inpass);
  }
#if defined(USE_WINDOWS_SSPI)
  else {
    rc = ldap_win_bind_auth(server, user, passwd, conn->data->set.httpauth);
  }
#endif

  return rc;
}