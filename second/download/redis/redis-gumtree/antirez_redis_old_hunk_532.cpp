            return;
        }
        serverLog(LL_VERBOSE,"Accepted connection to %s", server.unixsocket);
        acceptCommonHandler(cfd,CLIENT_UNIX_SOCKET);
    }
}

