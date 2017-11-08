static int ldap_win_bind_auth(LDAP *server, const char *user,
                              const char *passwd, unsigned long authflags)
{
  ULONG method = 0;
  SEC_WINNT_AUTH_IDENTITY cred = { 0, };
  int rc = LDAP_AUTH_METHOD_NOT_SUPPORTED;

#if defined(USE_SPNEGO)
  if(authflags & CURLAUTH_NEGOTIATE) {
    method = LDAP_AUTH_NEGOTIATE;
  }
  else
#endif
#if defined(USE_NTLM)
  if(authflags & CURLAUTH_NTLM) {
    method = LDAP_AUTH_NTLM;
  }
  else
#endif
#if !defined(CURL_DISABLE_CRYPTO_AUTH)
  if(authflags & CURLAUTH_DIGEST) {
    method = LDAP_AUTH_DIGEST;
  }
  else
#endif
  {
    /* required anyway if one of upper preprocessor definitions enabled */
  }

  if(method && user && passwd) {
    rc = Curl_create_sspi_identity(user, passwd, &cred);
    if(!rc) {
      rc = ldap_bind_s(server, NULL, (TCHAR *)&cred, method);
      Curl_sspi_free_identity(&cred);
    }
  }
  else {
    /* proceed with current user credentials */
    method = LDAP_AUTH_NEGOTIATE;
    rc = ldap_bind_s(server, NULL, NULL, method);
  }
  return rc;
}