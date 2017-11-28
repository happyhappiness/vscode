int Win32SockInit(void)
{
    int iVersionRequested;
    WSADATA wsaData;
    int err;

    if (s_iInitCount > 0) {
        ++s_iInitCount;
        return (0);
    } else if (s_iInitCount < 0)
        return (s_iInitCount);

    /* s_iInitCount == 0. Do the initailization */
    iVersionRequested = MAKEWORD(2, 0);

    err = WSAStartup((WORD) iVersionRequested, &wsaData);

    if (err) {
        s_iInitCount = -1;
        return (s_iInitCount);
    }

    if (LOBYTE(wsaData.wVersion) != 2 ||
            HIBYTE(wsaData.wVersion) != 0) {
        s_iInitCount = -2;
        WSACleanup();
        return (s_iInitCount);
    }

    ++s_iInitCount;
    return (s_iInitCount);
}