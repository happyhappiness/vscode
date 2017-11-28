inline int
WSASocket(int a, int t, int p, LPWSAPROTOCOL_INFO i, GROUP g, DWORD f)
{
    SOCKET result;
#ifdef UNICODE
    if ((result = ::WSASocketW(a, t, p, i, g, f)) == INVALID_SOCKET) {
#else
    if ((result = ::WSASocketA(a, t, p, i, g, f)) == INVALID_SOCKET) {
#endif
        if (WSAEMFILE == (errno = WSAGetLastError()))
            errno = EMFILE;
        return -1;
    } else
        return _open_osfhandle(result, 0);
}
#define WSASocket(a,t,p,i,g,f) Squid::WSASocket(a,t,p,i,g,f)

}