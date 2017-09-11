        return 0;
    }

    serverLog(REDIS_NOTICE, "supervised by systemd, will signal readyness");
    if ((fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
        serverLog(REDIS_WARNING,
                "Can't connect to systemd socket %s", notify_socket);
        return 0;
    }
