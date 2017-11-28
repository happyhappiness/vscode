const char * WINAPI SSP_ValidateNegotiateCredentials(PVOID PAutenticateBuf, int AutenticateLen, PBOOL fDone, int * Status, char * credentials)
{
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