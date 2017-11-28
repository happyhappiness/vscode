unsigned short
xatos(const char *token)
{
    long port = xatol(token);

    if (port & ~0xFFFF)
        self_destruct();

    return port;
}