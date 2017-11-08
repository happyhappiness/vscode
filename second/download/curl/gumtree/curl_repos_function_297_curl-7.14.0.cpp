void
Curl_ntlm_cleanup(struct connectdata *conn)
{
#ifdef USE_WINDOWS_SSPI
  ntlm_sspi_cleanup(&conn->ntlm);
  ntlm_sspi_cleanup(&conn->proxyntlm);
#else
  (void)conn;
#endif
}