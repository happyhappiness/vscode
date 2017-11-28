inline
struct hostent * gethostbyname (const char *n) {
    HOSTENT FAR * result;
    if ((result = ::gethostbyname(n)) == NULL)
        errno = WSAGetLastError();
    return result;
}