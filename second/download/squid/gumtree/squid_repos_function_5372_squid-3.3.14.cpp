int
logfile_mod_tcp_open(Logfile * lf, const char *path, size_t bufsz, int fatal_flag)
{
    debugs(5, 3, "Tcp Open called");
    Ip::Address addr;

    char *strAddr;

    lf->f_close = logfile_mod_tcp_close;
    lf->f_linewrite = logfile_mod_tcp_writeline;
    lf->f_linestart = logfile_mod_tcp_linestart;
    lf->f_lineend = logfile_mod_tcp_lineend;
    lf->f_flush = logfile_mod_tcp_flush;
    lf->f_rotate = logfile_mod_tcp_rotate;

    l_tcp_t *ll = static_cast<l_tcp_t*>(xcalloc(1, sizeof(*ll)));
    lf->data = ll;

    if (strncmp(path, "//", 2) == 0) {
        path += 2;
    }
    strAddr = xstrdup(path);

    if (!GetHostWithPort(strAddr, &addr)) {
        if (lf->flags.fatal) {
            fatalf("Invalid TCP logging address '%s'\n", lf->path);
        } else {
            debugs(50, DBG_IMPORTANT, "Invalid TCP logging address '" << lf->path << "'");
            safe_free(strAddr);
            return FALSE;
        }
    }

    safe_free(strAddr);

    Ip::Address any_addr;
    any_addr.SetAnyAddr();

    // require the sending TCP port to be of the right family for the destination address.
    if (addr.IsIPv4())
        any_addr.SetIPv4();

    ll->fd = comm_open(SOCK_STREAM, IPPROTO_TCP, any_addr, COMM_NONBLOCKING, "TCP log socket");
    if (ll->fd < 0) {
        if (lf->flags.fatal) {
            fatalf("Unable to open TCP socket for logging\n");
        } else {
            debugs(50, DBG_IMPORTANT, "Unable to open TCP socket for logging");
            return FALSE;
        }
    } else if (!comm_connect_addr(ll->fd, &addr)) {
        if (lf->flags.fatal) {
            fatalf("Unable to connect to %s for TCP log: %s\n", lf->path, xstrerror());
        } else {
            debugs(50, DBG_IMPORTANT, "Unable to connect to " << lf->path << " for TCP log: " << xstrerror());
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
            debugs(50, DBG_IMPORTANT, "logfileOpen (TCP): " << lf->path << ": " << xstrerror());
            return 0;
        }
    }

    bufsz = 65536;
    if (bufsz > 0) {
        ll->buf = static_cast<char*>(xmalloc(bufsz));
        ll->bufsz = bufsz;
    }

    return 1;
}