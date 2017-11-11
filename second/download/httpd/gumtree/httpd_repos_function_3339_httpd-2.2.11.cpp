static int UnregisterAppWithWinSock (void *nlm_handle)
{
    if (!WSACleanupWithNLMHandle)
    {
        if (!(WSACleanupWithNLMHandle = ImportPublicObject(gLibHandle, "WSACleanupWithNLMHandle")))
            WSACleanupWithNLMHandle = wsa_cleanup_with_handle;
    }

    return (*WSACleanupWithNLMHandle)(nlm_handle);
}