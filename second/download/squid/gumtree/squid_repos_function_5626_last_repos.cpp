static int
fdIsTcpListen(int fd)
{
    for (AnyP::PortCfgPointer s = HttpPortList; s != NULL; s = s->next) {
        if (s->listenConn != NULL && s->listenConn->fd == fd)
            return 1;
    }

    return 0;
}