CURLcode Curl_sspi_global_init(void)
{
  bool securityDll = FALSE;
  INITSECURITYINTERFACE_FN pInitSecurityInterface;

  /* If security interface is not yet initialized try to do this */
  if(!s_hSecDll) {
    /* Security Service Provider Interface (SSPI) functions are located in
     * security.dll on WinNT 4.0 and in secur32.dll on Win9x. Win2K and XP
     * have both these DLLs (security.dll forwards calls to secur32.dll) */
    DWORD majorVersion = 4;
    DWORD platformId = VER_PLATFORM_WIN32_NT;

#if !defined(_WIN32_WINNT) || !defined(_WIN32_WINNT_WIN2K) || \
    (_WIN32_WINNT < _WIN32_WINNT_WIN2K)
    OSVERSIONINFO osver;

    memset(&osver, 0, sizeof(osver));
    osver.dwOSVersionInfoSize = sizeof(osver);

    /* Find out Windows version */
    if(!GetVersionEx(&osver))
      return CURLE_FAILED_INIT;

    /* Verify the major version number == 4 and platform id == WIN_NT */
    if(osver.dwMajorVersion == majorVersion &&
       osver.dwPlatformId == platformId)
      securityDll = TRUE;
#else
    ULONGLONG majorVersionMask;
    ULONGLONG platformIdMask;
    OSVERSIONINFOEX osver;

    memset(&osver, 0, sizeof(osver));
    osver.dwOSVersionInfoSize = sizeof(osver);
    osver.dwMajorVersion = majorVersion;
    osver.dwPlatformId = platformId;
    majorVersionMask = VerSetConditionMask(0, VER_MAJORVERSION, VER_EQUAL);
    platformIdMask = VerSetConditionMask(0, VER_PLATFORMID, VER_EQUAL);

    /* Verify the major version number == 4 and platform id == WIN_NT */
    if(VerifyVersionInfo(&osver, VER_MAJORVERSION, majorVersionMask) &&
       VerifyVersionInfo(&osver, VER_PLATFORMID, platformIdMask))
      securityDll = TRUE;
#endif

    /* Load SSPI dll into the address space of the calling process */
    if(securityDll)
      s_hSecDll = LoadLibrary(TEXT("security.dll"));
    else
      s_hSecDll = LoadLibrary(TEXT("secur32.dll"));
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