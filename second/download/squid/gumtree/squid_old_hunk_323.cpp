        exit(1);
    }
    if (!*secretkey) {
        fprintf(stderr, "FATAL: %s: Shared secret not specified\n", argv[0]);
        exit(1);
    }
#if _SQUID_MSWIN_
    {
        WSADATA wsaData;
        WSAStartup(2, &wsaData);
        atexit(Win32SockCleanup);
    }
#endif
