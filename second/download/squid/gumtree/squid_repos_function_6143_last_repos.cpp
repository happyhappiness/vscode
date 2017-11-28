int
logfile_mod_udp_open(Logfile * lf, const char *path, size_t bufsz, int fatal_flag)
{
    Ip::Address addr;
    char *strAddr;

    lf->f_close = logfile_mod_udp_close;
    lf->f_linewrite = logfile_mod_udp_writeline;
    lf->f_linestart = logfile_mod_udp_linestart;
    lf->f_lineend = logfile_mod_udp_lineend;
    lf->f_flush = logfile_mod_udp_flush;
    lf->f_rotate = logfile_mod_udp_rotate;

    l_udp_t *ll = static_cast<l_udp_t*>(xcalloc(1, sizeof(*ll)));
    lf->data = ll;

    if (strncmp(path, "//", 2) == 0) {
        path += 2;
    }
    strAddr = xstrdup(path);
    if (!GetHostWithPort(strAddr, &addr)) {
        if (lf->flags.fatal) {
            fatalf("Invalid UDP logging address '%s'\n", lf->path);
        } else {
            debugs(50, DBG_IMPORTANT, "Invalid UDP logging address '" << lf->path << "'");
            safe_free(strAddr);
            return FALSE;
        }
    }
    safe_free(strAddr);

    Ip::Address any_addr;
    any_addr.setAnyAddr();

    // require the sending UDP port to be of the right family for the destination address.
    if (addr.isIPv4())
        any_addr.setIPv4();

    ll->fd = comm_open(SOCK_DGRAM, IPPROTO_UDP, any_addr, COMM_NONBLOCKING, "UDP log socket");
    int xerrno = errno;
    if (ll->fd < 0) {
        if (lf->flags.fatal) {
            fatalf("Unable to open UDP socket for logging\n");
        } else {
            debugs(50, DBG_IMPORTANT, "Unable to open UDP socket for logging");
            return FALSE;
        }
    } else if (!comm_connect_addr(ll->fd, addr)) {
        xerrno = errno;
        if (lf->flags.fatal) {
            fatalf("Unable to connect to %s for UDP log: %s\n", lf->path, xstrerr(xerrno));
        } else {
            debugs(50, DBG_IMPORTANT, "Unable to connect to " << lf->path << " for UDP log: " << xstrerr(xerrno));
            return FALSE;
        }
    }
    if (ll->fd == -1) {
        if (ENOENT == xerrno && fatal_flag) {
            fatalf("Cannot open '%s' because\n"
                   "\tthe parent directory does not exist.\n"
                   "\tPlease create the directory.\n", path);
        } else if (EACCES == xerrno && fatal_flag) {
            fatalf("Cannot open '%s' for writing.\n"
                   "\tThe parent directory must be writeable by the\n"
                   "\tuser '%s', which is the cache_effective_user\n"
                   "\tset in squid.conf.", path, Config.effectiveUser);
        } else {
            debugs(50, DBG_IMPORTANT, "logfileOpen (UDP): " << lf->path << ": " << xstrerr(xerrno));
            return 0;
        }
    }
    /* Force buffer size to something roughly fitting inside an MTU */
    /*
     * XXX note the receive side needs to receive the whole packet at once;
     * applications like netcat have a small default receive buffer and will
     * truncate!
     */
    bufsz = 1400;
    if (bufsz > 0) {
        ll->buf = static_cast<char*>(xmalloc(bufsz));
        ll->bufsz = bufsz;
    }

    return 1;
}