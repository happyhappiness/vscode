static int Win32SockInit(void)
{
    int iVersionRequested;
    WSADATA wsaData;
    int err, opt;
    int optlen = sizeof(opt);

    if (s_iInitCount > 0) {
        s_iInitCount++;
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

    if (WIN32_OS_version !=_WIN_OS_WINNT) {
        if (::getsockopt(INVALID_SOCKET, SOL_SOCKET, SO_OPENTYPE, (char *)&opt, &optlen)) {
            s_iInitCount = -3;
            WSACleanup();
            return (s_iInitCount);
        } else {
            opt = opt | SO_SYNCHRONOUS_NONALERT;

            if (::setsockopt(INVALID_SOCKET, SOL_SOCKET, SO_OPENTYPE, (char *) &opt, optlen)) {
                s_iInitCount = -3;
                WSACleanup();
                return (s_iInitCount);
            }
        }
    }

    WIN32_Socks_initialized = 1;
    s_iInitCount++;
    return (s_iInitCount);
}