void
accessLogLog(AccessLogEntry::Pointer &al, ACLChecklist * checklist)
{
    if (LogfileStatus != LOG_ENABLE)
        return;

    accessLogLogTo(Config.Log.accesslogs, al, checklist);
#if MULTICAST_MISS_STREAM

    if (al->cache.code != LOG_TCP_MISS)
        (void) 0;
    else if (al->http.method != METHOD_GET)
        (void) 0;
    else if (mcast_miss_fd < 0)
        (void) 0;
    else {
        unsigned int ibuf[365];
        size_t isize;
        xstrncpy((char *) ibuf, al->url, 364 * sizeof(int));
        isize = ((strlen(al->url) + 8) / 8) * 2;

        if (isize > 364)
            isize = 364;

        mcast_encode((unsigned int *) ibuf, isize,
                     (const unsigned int *) Config.mcast_miss.encode_key);

        comm_udp_sendto(mcast_miss_fd,
                        &mcast_miss_to, sizeof(mcast_miss_to),
                        ibuf, isize * sizeof(int));
    }

#endif
}