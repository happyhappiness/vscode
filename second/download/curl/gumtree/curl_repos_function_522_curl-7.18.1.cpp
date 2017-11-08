void
Curl_ntlm_cleanup(struct connectdata *conn)
{
#ifdef USE_WINDOWS_SSPI
  ntlm_sspi_cleanup(&conn->ntlm);
  ntlm_sspi_cleanup(&conn->proxyntlm);
  if(s_hSecDll != NULL) {
    FreeLibrary(s_hSecDll);
    s_hSecDll = NULL;
    s_pSecFn = NULL;
  }
#else
  (void)conn;
#endif
}