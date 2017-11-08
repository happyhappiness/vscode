static int RegisterAppWithWinSock (void *nlm_handle)
{
    int err;
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(WSAHighByte, WSALowByte);

    if (!WSAStartupWithNLMHandle)
    {
        if (!(WSAStartupWithNLMHandle = ImportPublicObject(gLibHandle, "WSAStartupWithNLMHandle")))
            WSAStartupWithNLMHandle = wsa_startup_with_handle;
    }

    err = (*WSAStartupWithNLMHandle)(wVersionRequested, &wsaData, nlm_handle);

    if (LOBYTE(wsaData.wVersion) != WSAHighByte ||
        HIBYTE(wsaData.wVersion) != WSALowByte) {
        
        UnregisterAppWithWinSock (nlm_handle);
        return APR_EEXIST;
    }

    return err;
}