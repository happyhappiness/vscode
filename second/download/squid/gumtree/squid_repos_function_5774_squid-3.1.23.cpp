void UnloadSecurityDll(void)
{
    if (NTLM_asServer.fHaveCtxtHandle)
        _DeleteSecurityContext(&NTLM_asServer.hctxt);
    if (NTLM_asServer.fHaveCredHandle)
        _FreeCredentialsHandle(&NTLM_asServer.hcred);

    if (hModule)
        FreeLibrary(hModule);

    xfree(SSP_Package_InUse);
    xfree(pClientBuf);
    xfree(pServerBuf);

    _AcceptSecurityContext      = NULL;
    _AcquireCredentialsHandle   = NULL;
    _CompleteAuthToken          = NULL;
    _DeleteSecurityContext      = NULL;
    _FreeContextBuffer          = NULL;
    _FreeCredentialsHandle      = NULL;
    _InitializeSecurityContext  = NULL;
    _QuerySecurityPackageInfo   = NULL;
    _QueryContextAttributes     = NULL;

    hModule = NULL;
}