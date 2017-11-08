void Curl_sasl_cleanup(struct connectdata *conn, unsigned int authused)
{
#ifdef USE_NTLM
  /* Cleanup the ntlm structure */
  if(authused == SASL_MECH_NTLM) {
    Curl_ntlm_sspi_cleanup(&conn->ntlm);
  }
  (void)conn;
#else
  /* Reserved for future use */
  (void)conn;
  (void)authused;
#endif
}