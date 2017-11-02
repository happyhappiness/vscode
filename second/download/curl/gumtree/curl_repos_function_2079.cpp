void Curl_http_ntlm_cleanup(struct connectdata *conn)
{
  Curl_sasl_ntlm_cleanup(&conn->ntlm);
  Curl_sasl_ntlm_cleanup(&conn->proxyntlm);

#if defined(NTLM_WB_ENABLED)
  Curl_ntlm_wb_cleanup(conn);
#endif
}