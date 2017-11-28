const char * WINAPI SSP_MakeChallenge(PVOID PNegotiateBuf, int NegotiateLen)
{
    BOOL        fDone      = FALSE;
    PVOID       fResult    = NULL;
    DWORD       cbOut      = 0;
    DWORD       cbIn       = 0;
    ntlm_challenge * challenge;

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
        struct base64_encode_ctx ctx;
        base64_encode_init(&ctx);
        static uint8_t encoded[8192];
        size_t dstLen = base64_encode_update(&ctx, encoded, cbOut, reinterpret_cast<const uint8_t*>(fResult));
        assert(dstLen < sizeof(encoded));
        dstLen += base64_encode_final(&ctx, encoded+dstLen);
        assert(dstLen < sizeof(encoded));
        encoded[dstLen] = '\0';
        return reinterpret_cast<char *>(encoded);
    }
    return NULL;
}