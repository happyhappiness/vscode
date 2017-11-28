inline int
socket(int f, int t, int p)
{
    SOCKET result;
    if ((result = ::socket(f, t, p)) == INVALID_SOCKET) {
        if (WSAEMFILE == (errno = WSAGetLastError()))
            errno = EMFILE;
        return -1;
    } else
        return _open_osfhandle(result, 0);
}