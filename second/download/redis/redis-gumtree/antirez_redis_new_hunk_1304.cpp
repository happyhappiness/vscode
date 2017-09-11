        cfd = anetUnixAccept(server.neterr, fd);
        if (cfd == ANET_ERR) {
            if (errno != EWOULDBLOCK)
                serverLog(REDIS_WARNING,
                    "Accepting client connection: %s", server.neterr);
            return;
        }
        serverLog(REDIS_VERBOSE,"Accepted connection to %s", server.unixsocket);
        acceptCommonHandler(cfd,REDIS_UNIX_SOCKET);
    }
}
