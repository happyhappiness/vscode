void
accessLogInit(void)
{
    customlog *log;

    accessLogRegisterWithCacheManager();

    assert(sizeof(log_tags) == (LOG_TYPE_MAX + 1) * sizeof(char *));

#if USE_ADAPTATION
    alLogformatHasAdaptToken = false;
#endif
#if ICAP_CLIENT
    alLogformatHasIcapToken = false;
#endif

    for (log = Config.Log.accesslogs; log; log = log->next) {
        if (log->type == CLF_NONE)
            continue;

        log->logfile = logfileOpen(log->filename, MAX_URL << 1, 1);

        LogfileStatus = LOG_ENABLE;

#if USE_ADAPTATION || ICAP_CLIENT
        for (logformat_token * curr_token = (log->logFormat?log->logFormat->format:NULL); curr_token; curr_token = curr_token->next) {
#if USE_ADAPTATION
            if (curr_token->type == LTF_ADAPTATION_SUM_XACT_TIMES ||
                    curr_token->type == LTF_ADAPTATION_ALL_XACT_TIMES) {
                alLogformatHasAdaptToken = true;
            }
#endif
#if ICAP_CLIENT
            if (curr_token->type == LFT_ICAP_LAST_MATCHED_HEADER ||
                    curr_token->type == LFT_ICAP_LAST_MATCHED_HEADER_ELEM ||
                    curr_token->type == LFT_ICAP_LAST_MATCHED_ALL_HEADERS) {
                alLogformatHasIcapToken = true;
            }
#endif
        }
#endif
    }

#if HEADERS_LOG

    headerslog = logfileOpen("/usr/local/squid/logs/headers.log", 512);

    assert(NULL != headerslog);

#endif
#if MULTICAST_MISS_STREAM

    if (Config.mcast_miss.addr.s_addr != no_addr.s_addr) {
        memset(&mcast_miss_to, '\0', sizeof(mcast_miss_to));
        mcast_miss_to.sin_family = AF_INET;
        mcast_miss_to.sin_port = htons(Config.mcast_miss.port);
        mcast_miss_to.sin_addr.s_addr = Config.mcast_miss.addr.s_addr;
        mcast_miss_fd = comm_open(SOCK_DGRAM,
                                  IPPROTO_UDP,
                                  Config.Addrs.udp_incoming,
                                  Config.mcast_miss.port,
                                  COMM_NONBLOCKING,
                                  "Multicast Miss Stream");

        if (mcast_miss_fd < 0)
            fatal("Cannot open Multicast Miss Stream Socket");

        debugs(46, 1, "Multicast Miss Stream Socket opened on FD " << mcast_miss_fd);

        mcastSetTtl(mcast_miss_fd, Config.mcast_miss.ttl);

        if (strlen(Config.mcast_miss.encode_key) < 16)
            fatal("mcast_encode_key is too short, must be 16 characters");
    }

#endif
#if FORW_VIA_DB

    fvdbInit();

#endif
}