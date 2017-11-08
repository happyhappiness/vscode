int _NonAppStart
(
    void        *NLMHandle,
    void        *errorScreen,
    const char  *cmdLine,
    const char  *loadDirPath,
    size_t      uninitializedDataLength,
    void        *NLMFileHandle,
    int         (*readRoutineP)( int conn, void *fileHandle, size_t offset,
                    size_t nbytes, size_t *bytesRead, void *buffer ),
    size_t      customDataOffset,
    size_t      customDataSize,
    int         messageCount,
    const char  **messages
)
{
    WSADATA wsaData;
    apr_status_t status;

    NX_LOCK_INFO_ALLOC(liblock, "Per-Application Data Lock", 0);

#pragma unused(cmdLine)
#pragma unused(loadDirPath)
#pragma unused(uninitializedDataLength)
#pragma unused(NLMFileHandle)
#pragma unused(readRoutineP)
#pragma unused(customDataOffset)
#pragma unused(customDataSize)
#pragma unused(messageCount)
#pragma unused(messages)

    
    gLibId = register_library(DisposeLibraryData);

    if (gLibId < -1)
    {
        OutputToScreen(errorScreen, "Unable to register library with kernel.\n");
        return -1;
    }

    gLibHandle = NLMHandle;

    gLibLock = NXMutexAlloc(0, 0, &liblock);

    if (!gLibLock)
    {
        OutputToScreen(errorScreen, "Unable to allocate library data lock.\n");
        return -1;
    }

    apr_netware_setup_time();

    if ((status = apr_pool_initialize()) != APR_SUCCESS)
        return status;

    return WSAStartup((WORD) MAKEWORD(2, 0), &wsaData);
}