void Curl_sasl_cleanup(struct connectdata *conn, unsigned int authused)
{
#if defined(USE_KERBEROS5)
  /* Cleanup the gssapi structure */
  if(authused == SASL_MECH_GSSAPI) {
    Curl_sasl_gssapi_cleanup(&conn->krb5);
  }
#endif

#if defined(USE_NTLM)
  /* Cleanup the ntlm structure */
  if(authused == SASL_MECH_NTLM) {
    Curl_sasl_ntlm_cleanup(&conn->ntlm);
  }
#endif

#if !defined(USE_KERBEROS5) && !defined(USE_NTLM)
  /* Reserved for future use */
  (void)conn;
  (void)authused;
#endif
}