    int sendto_flags = 0;

    if (!notify_socket) {
        serverLog(REDIS_WARNING,
                "systemd supervision requested, but NOTIFY_SOCKET not found");
        return 0;
    }
