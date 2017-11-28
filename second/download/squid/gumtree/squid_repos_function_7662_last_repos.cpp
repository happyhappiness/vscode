const char * WINAPI SSP_MakeNegotiateBlob(PVOID PNegotiateBuf, int NegotiateLen, PBOOL fDone, int * Status, char * credentials)
{
    DWORD       cbOut      = 0;
    DWORD       cbIn       = 0;

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
    if (pServerBuf != NULL && cbOut > 0) {
        struct base64_encode_ctx ctx;
        base64_encode_init(&ctx);
        static uint8_t encoded[8192];
        size_t dstLen = base64_encode_update(&ctx, encoded, cbOut, reinterpret_cast<const uint8_t*>(pServerBuf));
        assert(dstLen < sizeof(encoded));
        dstLen += base64_encode_final(&ctx, encoded+dstLen);
        assert(dstLen < sizeof(encoded));
        encoded[dstLen] = '\0';
        return reinterpret_cast<char *>(encoded);
    }
    return NULL;
}