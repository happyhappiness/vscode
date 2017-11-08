void Curl_http_ntlm_cleanup(struct connectdata *conn)
{
#ifdef USE_WINDOWS_SSPI
  Curl_ntlm_sspi_cleanup(&conn->ntlm);
  Curl_ntlm_sspi_cleanup(&conn->proxyntlm);
#elif defined(NTLM_WB_ENABLED)
  Curl_ntlm_wb_cleanup(conn);
#else
  (void)conn;
#endif
}