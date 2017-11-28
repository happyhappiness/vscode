
    // require the sending UDP port to be of the right family for the destination address.
    if (addr.isIPv4())
        any_addr.setIPv4();

    ll->fd = comm_open(SOCK_DGRAM, IPPROTO_UDP, any_addr, COMM_NONBLOCKING, "UDP log socket");
    if (ll->fd < 0) {
        if (lf->flags.fatal) {
            fatalf("Unable to open UDP socket for logging\n");
        } else {
            debugs(50, DBG_IMPORTANT, "Unable to open UDP socket for logging");
            return FALSE;
        }
    } else if (!comm_connect_addr(ll->fd, addr)) {
        if (lf->flags.fatal) {
            fatalf("Unable to connect to %s for UDP log: %s\n", lf->path, xstrerror());
        } else {
            debugs(50, DBG_IMPORTANT, "Unable to connect to " << lf->path << " for UDP log: " << xstrerror());
            return FALSE;
        }
    }
    if (ll->fd == -1) {
        if (ENOENT == errno && fatal_flag) {
            fatalf("Cannot open '%s' because\n"
                   "\tthe parent directory does not exist.\n"
                   "\tPlease create the directory.\n", path);
        } else if (EACCES == errno && fatal_flag) {
            fatalf("Cannot open '%s' for writing.\n"
                   "\tThe parent directory must be writeable by the\n"
                   "\tuser '%s', which is the cache_effective_user\n"
                   "\tset in squid.conf.", path, Config.effectiveUser);
        } else {
            debugs(50, DBG_IMPORTANT, "logfileOpen (UDP): " << lf->path << ": " << xstrerror());
            return 0;
        }
    }
    /* Force buffer size to something roughly fitting inside an MTU */
    /*
     * XXX note the receive side needs to receive the whole packet at once;
