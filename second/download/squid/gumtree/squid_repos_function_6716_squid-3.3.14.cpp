const char * WINAPI SSP_MakeNegotiateBlob(PVOID PNegotiateBuf, int NegotiateLen, PBOOL fDone, int * Status, char * credentials)
{
    DWORD       cbOut      = 0;
    DWORD       cbIn       = 0;
    const char * encoded = NULL;

    if (NTLM_asServer.fHaveCtxtHandle)
        _DeleteSecurityContext(&NTLM_asServer.hctxt);
    if (NTLM_asServer.fHaveCredHandle)
        _FreeCredentialsHandle(&NTLM_asServer.hcred);

    memcpy(pClientBuf, PNegotiateBuf, NegotiateLen);
    ZeroMemory(pServerBuf, cbMaxToken);
    ZeroMemory(&NTLM_asServer, sizeof(NTLM_asServer));
    do {
        if (!hModule)
            break;

        /* Prepare server message (challenge) */
        cbIn = NegotiateLen;
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