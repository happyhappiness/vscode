            return FALSE;
        }
    }
    safe_free(strAddr);

    Ip::Address any_addr;
    any_addr.SetAnyAddr();

    // require the sending UDP port to be of the right family for the destination address.
    if (addr.IsIPv4())
        any_addr.SetIPv4();

    ll->fd = comm_open(SOCK_DGRAM, IPPROTO_UDP, any_addr, COMM_NONBLOCKING, "UDP log socket");
    if (ll->fd < 0) {
        if (lf->flags.fatal) {
            fatalf("Unable to open UDP socket for logging\n");
        } else {
            debugs(50, DBG_IMPORTANT, "Unable to open UDP socket for logging");
            return FALSE;
        }
    } else if (!comm_connect_addr(ll->fd, &addr)) {
        if (lf->flags.fatal) {
            fatalf("Unable to connect to %s for UDP log: %s\n", lf->path, xstrerror());
        } else {
            debugs(50, DBG_IMPORTANT, "Unable to connect to " << lf->path << " for UDP log: " << xstrerror());
            return FALSE;
        }
