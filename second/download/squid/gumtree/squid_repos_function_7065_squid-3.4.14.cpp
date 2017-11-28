inline HOSTENT FAR *
gethostbyaddr(const void * a, size_t l, int t)
{
    HOSTENT FAR * result;
    if ((result = ::gethostbyaddr((const char*)a, l, t)) == NULL)
        errno = WSAGetLastError();
    return result;
}