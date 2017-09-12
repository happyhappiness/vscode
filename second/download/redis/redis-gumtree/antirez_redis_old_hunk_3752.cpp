    return ANET_OK;
}

#define ANET_CONNECT_NONE 0
#define ANET_CONNECT_NONBLOCK 1
static int anetTcpGenericConnect(char *err, char *addr, int port, int flags)
{
    int s, on = 1;
    struct sockaddr_in sa;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        anetSetError(err, "creating socket: %s\n", strerror(errno));
        return ANET_ERR;
    }
    /* Make sure connection-intensive things like the redis benckmark
     * will be able to close/open sockets a zillion of times */
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
