const char * WINAPI SSP_ValidateNegotiateCredentials(PVOID PAutenticateBuf, int AutenticateLen, PBOOL fDone, int * Status, char * credentials)
{
    DWORD       cbOut      = 0;
    DWORD       cbIn       = 0;
    const char * encoded = NULL;

    memcpy(pClientBuf, PAutenticateBuf, AutenticateLen);
    ZeroMemory(pServerBuf, cbMaxToken);
    do {
        if (!hModule)
            break;

        /* Prepare server message (authentication) */
        cbIn = AutenticateLen;
        cbOut = cbMaxToken;
        if (!GenServerContext(&NTLM_asServer, pClientBuf, cbIn, pServerBuf, &cbOut,
                              fDone, credentials)) {
            *Status = SSP_ERROR;
            break;
        }
        *Status = SSP_OK;
    } while (0);
    if (pServerBuf != NULL && cbOut > 0)
        encoded = base64_encode_bin((char *) pServerBuf, cbOut);
    return encoded;
}