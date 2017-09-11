    return ANET_OK;
}

int anetTcpServer(char *err, int port, char *bindaddr)
{
    int s, rv;
