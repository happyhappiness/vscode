void
DiskdIOStrategy::sync()
{
    static time_t lastmsg = 0;

    while (away > 0) {
        if (squid_curtime > lastmsg) {
            debugs(47, DBG_IMPORTANT, "storeDiskdDirSync: " << away << " messages away");
            lastmsg = squid_curtime;
        }

        callback();
    }
}