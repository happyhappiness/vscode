inline
int WSAAsyncSelect(int s, HWND h, unsigned int w, long e)
{
    if (::WSAAsyncSelect(_get_osfhandle(s), h, w, e) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return 0;
}