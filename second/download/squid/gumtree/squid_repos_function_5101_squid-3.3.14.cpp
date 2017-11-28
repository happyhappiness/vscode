static int
fdIsTcpListen(int fd)
{
    for (const AnyP::PortCfg *s = Config.Sockaddr.http; s; s = s->next) {
        if (s->listenConn != NULL && s->listenConn->fd == fd)
            return 1;
    }

    return 0;
}