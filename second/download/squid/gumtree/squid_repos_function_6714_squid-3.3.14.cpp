const char * WINAPI SSP_MakeChallenge(PVOID PNegotiateBuf, int NegotiateLen)
{
    BOOL        fDone      = FALSE;
    PVOID       fResult    = NULL;
    DWORD       cbOut      = 0;
    DWORD       cbIn       = 0;
    ntlm_challenge * challenge;
    const char * encoded = NULL;

    if (NTLM_asServer.fHaveCtxtHandle)
        _DeleteSecurityContext(&NTLM_asServer.hctxt);
    if (NTLM_asServer.fHaveCredHandle)
        _FreeCredentialsHandle(&NTLM_asServer.hcred);

    NTLM_LocalCall = FALSE;
    Use_Unicode = FALSE;
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
                              &fDone, NULL))
            break;
        fResult = pServerBuf;
    } while (0);
    if (fResult != NULL) {
        challenge = (ntlm_challenge *) fResult;
        Use_Unicode = NTLM_NEGOTIATE_UNICODE & challenge->flags;
        NTLM_LocalCall = NTLM_NEGOTIATE_THIS_IS_LOCAL_CALL & challenge->flags;
        encoded = base64_encode_bin((char *) fResult, cbOut);
    }
    return encoded;
}