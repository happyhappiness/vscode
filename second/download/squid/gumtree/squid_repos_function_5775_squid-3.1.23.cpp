HMODULE LoadSecurityDll(int mode, char * SSP_Package)
{
    TCHAR lpszDLL[MAX_PATH];
    OSVERSIONINFO VerInfo;
    PSecPkgInfo pSPI       = NULL;

    /*
    *  Find out which security DLL to use, depending on
    *  whether we are on NT or 2000 or XP or 2003 Server
    *  We have to use security.dll on Windows NT 4.0.
    *  All other operating systems, we have to use Secur32.dll
    */
    hModule = NULL;
    if ((mode != SSP_BASIC) && (mode != SSP_NTLM))
        return hModule;
    NTLM_mode = mode;
    VerInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    if (!GetVersionEx (&VerInfo)) {   /* If this fails, something has gone wrong */
        return hModule;
    }
    if (VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT &&
            VerInfo.dwMajorVersion == 4 &&
            VerInfo.dwMinorVersion == 0) {
        lstrcpy (lpszDLL, _T(WINNT_SECURITY_DLL));
    } else {
        lstrcpy (lpszDLL, _T(WIN2K_SECURITY_DLL));
    }
    hModule = LoadLibrary(lpszDLL);
    if (!hModule)
        return hModule;
    _AcceptSecurityContext = (ACCEPT_SECURITY_CONTEXT_FN)
                             GetProcAddress(hModule, "AcceptSecurityContext");
    if (!_AcceptSecurityContext) {
        UnloadSecurityDll();
        hModule = NULL;
        return hModule;
    }
#ifdef UNICODE
    _AcquireCredentialsHandle = (ACQUIRE_CREDENTIALS_HANDLE_FN)
                                GetProcAddress(hModule, "AcquireCredentialsHandleW");
#else
    _AcquireCredentialsHandle = (ACQUIRE_CREDENTIALS_HANDLE_FN)
                                GetProcAddress(hModule, "AcquireCredentialsHandleA");
#endif
    if (!_AcquireCredentialsHandle) {
        UnloadSecurityDll();
        hModule = NULL;
        return hModule;
    }
    _CompleteAuthToken = (COMPLETE_AUTH_TOKEN_FN)
                         GetProcAddress(hModule, "CompleteAuthToken");
    if (!_CompleteAuthToken) {
        UnloadSecurityDll();
        hModule = NULL;
        return hModule;
    }
    _DeleteSecurityContext = (DELETE_SECURITY_CONTEXT_FN)
                             GetProcAddress(hModule, "DeleteSecurityContext");
    if (!_DeleteSecurityContext) {
        UnloadSecurityDll();
        hModule = NULL;
        return hModule;
    }
    _FreeContextBuffer = (FREE_CONTEXT_BUFFER_FN)
                         GetProcAddress(hModule, "FreeContextBuffer");
    if (!_FreeContextBuffer) {
        UnloadSecurityDll();
        hModule = NULL;
        return hModule;
    }
    _FreeCredentialsHandle = (FREE_CREDENTIALS_HANDLE_FN)
                             GetProcAddress(hModule, "FreeCredentialsHandle");
    if (!_FreeCredentialsHandle) {
        UnloadSecurityDll();
        hModule = NULL;
        return hModule;
    }
#ifdef UNICODE
    _InitializeSecurityContext = (INITIALIZE_SECURITY_CONTEXT_FN)
                                 GetProcAddress(hModule, "InitializeSecurityContextW");
#else
    _InitializeSecurityContext = (INITIALIZE_SECURITY_CONTEXT_FN)
                                 GetProcAddress(hModule, "InitializeSecurityContextA");
#endif
    if (!_InitializeSecurityContext) {
        UnloadSecurityDll();
        hModule = NULL;
        return hModule;
    }
#ifdef UNICODE
    _QuerySecurityPackageInfo = (QUERY_SECURITY_PACKAGE_INFO_FN)
                                GetProcAddress(hModule, "QuerySecurityPackageInfoW");
#else
    _QuerySecurityPackageInfo = (QUERY_SECURITY_PACKAGE_INFO_FN)
                                GetProcAddress(hModule, "QuerySecurityPackageInfoA");
#endif
    if (!_QuerySecurityPackageInfo) {
        UnloadSecurityDll();
        hModule = NULL;
    }

#ifdef UNICODE
    _QueryContextAttributes = (QUERY_CONTEXT_ATTRIBUTES_FN_W)
                              GetProcAddress(hModule, "QueryContextAttributesW");
#else
    _QueryContextAttributes = (QUERY_CONTEXT_ATTRIBUTES_FN_A)
                              GetProcAddress(hModule, "QueryContextAttributesA");
#endif
    if (!_QueryContextAttributes) {
        UnloadSecurityDll();
        hModule = NULL;
    }

    /* Get max token size */
    _QuerySecurityPackageInfo((SEC_CHAR*)_T(SSP_Package), &pSPI);
    cbMaxToken = pSPI->cbMaxToken;
    _FreeContextBuffer(pSPI);

    /* Allocate buffers for client and server messages */
    pClientBuf = xcalloc(cbMaxToken, sizeof(char));
    pServerBuf = xcalloc(cbMaxToken, sizeof(char));
    SSP_Package_InUse = xstrdup(SSP_Package);

    return hModule;
}