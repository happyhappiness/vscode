        cfd = anetTcpAccept(server.neterr, fd, cip, sizeof(cip), &cport);
        if (cfd == ANET_ERR) {
            if (errno != EWOULDBLOCK)
                serverLog(REDIS_WARNING,
                    "Accepting client connection: %s", server.neterr);
            return;
        }
        serverLog(REDIS_VERBOSE,"Accepted %s:%d", cip, cport);
        acceptCommonHandler(cfd,0);
    }
}
