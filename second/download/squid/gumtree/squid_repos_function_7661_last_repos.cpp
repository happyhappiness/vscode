BOOL WINAPI SSP_ValidateNTLMCredentials(PVOID PAutenticateBuf, int AutenticateLen, char * credentials)
{
    BOOL        fDone      = FALSE;
    BOOL        fResult    = FALSE;
    DWORD       cbOut      = 0;
    DWORD       cbIn       = 0;

    memcpy(pClientBuf, PAutenticateBuf, AutenticateLen);
    ZeroMemory(pServerBuf, cbMaxToken);
    do {
        if (!hModule)
            break;

        /* Prepare server message (authentication) */
        cbIn = AutenticateLen;
        cbOut = cbMaxToken;
        if (!GenServerContext(&NTLM_asServer, pClientBuf, cbIn, pServerBuf, &cbOut,
                              &fDone, credentials))
            break;
        fResult = TRUE;
    } while (0);

    return fResult;
}