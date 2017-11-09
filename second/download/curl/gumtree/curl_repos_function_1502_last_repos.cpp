void Curl_sspi_global_cleanup(void)
{
  if(s_hSecDll) {
    FreeLibrary(s_hSecDll);
    s_hSecDll = NULL;
    s_pSecFn = NULL;
  }
}