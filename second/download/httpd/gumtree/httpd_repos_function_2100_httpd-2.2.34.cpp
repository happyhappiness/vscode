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
#pragma unused(cmdLine)
#pragma unused(loadDirPath)
#pragma unused(uninitializedDataLength)
#pragma unused(NLMFileHandle)
#pragma unused(readRoutineP)
#pragma unused(customDataOffset)
#pragma unused(customDataSize)
#pragma unused(messageCount)
#pragma unused(messages)

    /* register for down server event */
    rtag_t rt = AllocateResourceTag(NLMHandle, "Apache2 Down Server Callback",
                                    EventSignature);

    NX_WRAP_INTERFACE((void *)ap_down_server_cb, 2, (void **)&ref);
    NX_WRAP_INTERFACE((void *)ap_dummy_cb, 2, (void **)&dum);
    eh = RegisterForEventNotification(rt, EVENT_DOWN_SERVER,
                                      EVENT_PRIORITY_APPLICATION,
                                      ref, dum, NULL);

    /* clean-up */
    NXVmRegisterExitHandler(ap_cb_destroy, NULL);

    return 0;
}