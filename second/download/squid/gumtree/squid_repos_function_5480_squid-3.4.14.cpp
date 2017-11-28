void
accessLogInit(void)
{
    CustomLog *log;

    accessLogRegisterWithCacheManager();

#if USE_ADAPTATION
    Log::TheConfig.hasAdaptToken = false;
#endif
#if ICAP_CLIENT
    Log::TheConfig.hasIcapToken = false;
#endif

    for (log = Config.Log.accesslogs; log; log = log->next) {
        if (log->type == Log::Format::CLF_NONE)
            continue;

        log->logfile = logfileOpen(log->filename, log->bufferSize, log->fatal);

        LogfileStatus = LOG_ENABLE;

#if USE_ADAPTATION
        for (Format::Token * curr_token = (log->logFormat?log->logFormat->format:NULL); curr_token; curr_token = curr_token->next) {
            if (curr_token->type == Format::LFT_ADAPTATION_SUM_XACT_TIMES ||
                    curr_token->type == Format::LFT_ADAPTATION_ALL_XACT_TIMES ||
                    curr_token->type == Format::LFT_ADAPTATION_LAST_HEADER ||
                    curr_token->type == Format::LFT_ADAPTATION_LAST_HEADER_ELEM ||
                    curr_token->type == Format::LFT_ADAPTATION_LAST_ALL_HEADERS||
                    (curr_token->type == Format::LFT_NOTE && !Adaptation::Config::metaHeaders.empty())) {
                Log::TheConfig.hasAdaptToken = true;
            }
#if ICAP_CLIENT
            if (curr_token->type == Format::LFT_ICAP_TOTAL_TIME) {
                Log::TheConfig.hasIcapToken = true;
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

        debugs(46, DBG_IMPORTANT, "Multicast Miss Stream Socket opened on FD " << mcast_miss_fd);

        mcastSetTtl(mcast_miss_fd, Config.mcast_miss.ttl);

        if (strlen(Config.mcast_miss.encode_key) < 16)
            fatal("mcast_encode_key is too short, must be 16 characters");
    }

#endif
#if USE_FORW_VIA_DB

    fvdbInit();

#endif
}