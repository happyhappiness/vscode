inline int
read(int fd, void * buf, size_t siz)
{
    char l_so_type[sizeof(int)];
    int l_so_type_siz = sizeof(l_so_type);
    SOCKET sock = _get_osfhandle(fd);

    if (::getsockopt(sock, SOL_SOCKET, SO_TYPE, l_so_type, &l_so_type_siz) == 0)
        return ::recv(sock, (char FAR *) buf, (int)siz, 0);
    else
        return _read(fd, buf, (unsigned int)siz);
}