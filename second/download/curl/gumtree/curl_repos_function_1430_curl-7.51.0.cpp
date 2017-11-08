CURLcode Curl_sspi_global_init(void)
{
  INITSECURITYINTERFACE_FN pInitSecurityInterface;

  /* If security interface is not yet initialized try to do this */
  if(!s_hSecDll) {
    /* Security Service Provider Interface (SSPI) functions are located in
     * security.dll on WinNT 4.0 and in secur32.dll on Win9x. Win2K and XP
     * have both these DLLs (security.dll forwards calls to secur32.dll) */

    /* Load SSPI dll into the address space of the calling process */
    if(Curl_verify_windows_version(4, 0, PLATFORM_WINNT, VERSION_EQUAL))
      s_hSecDll = Curl_load_library(TEXT("security.dll"));
    else
      s_hSecDll = Curl_load_library(TEXT("secur32.dll"));
    if(!s_hSecDll)
      return CURLE_FAILED_INIT;

    /* Get address of the InitSecurityInterfaceA function from the SSPI dll */
    pInitSecurityInterface = (INITSECURITYINTERFACE_FN)
      GetProcAddress(s_hSecDll, SECURITYENTRYPOINT);
    if(!pInitSecurityInterface)
      return CURLE_FAILED_INIT;

    /* Get pointer to Security Service Provider Interface dispatch table */
    s_pSecFn = pInitSecurityInterface();
    if(!s_pSecFn)
      return CURLE_FAILED_INIT;
  }

  return CURLE_OK;
}