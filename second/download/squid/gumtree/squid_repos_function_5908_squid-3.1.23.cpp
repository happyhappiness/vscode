inline
SERVENT FAR* getservbyname (const char * n, const char * p)
{
    SERVENT FAR * result;
    if ((result = ::getservbyname(n, p)) == NULL)
        errno = WSAGetLastError();
    return result;
}