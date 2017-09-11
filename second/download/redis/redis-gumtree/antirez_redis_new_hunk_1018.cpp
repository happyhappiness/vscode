        return 0;
    }

    serverLog(LL_NOTICE, "supervised by systemd, will signal readyness");
    if ((fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
        serverLog(LL_WARNING,
                "Can't connect to systemd socket %s", notify_socket);
        return 0;
    }
