inline
HOSTENT FAR * gethostbyaddr(const char * a, int l, int t)
{
    HOSTENT FAR * result;
    if ((result = ::gethostbyaddr(a, l, t)) == NULL)
        errno = WSAGetLastError();
    return result;
}