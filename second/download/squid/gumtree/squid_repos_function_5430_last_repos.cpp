void
memConfigure(void)
{
    int64_t new_pool_limit;

    /** Set to configured value first */
    if (!Config.onoff.mem_pools)
        new_pool_limit = 0;
    else if (Config.MemPools.limit > 0)
        new_pool_limit = Config.MemPools.limit;
    else {
        if (Config.MemPools.limit == 0)
            debugs(13, DBG_IMPORTANT, "memory_pools_limit 0 has been chagned to memory_pools_limit none. Please update your config");
        new_pool_limit = -1;
    }

#if 0
    /** \par
     * DPW 2007-04-12
     * No debugging here please because this method is called before
     * the debug log is configured and we'll get the message on
     * stderr when doing things like 'squid -k reconfigure'
     */
    if (MemPools::GetInstance().idleLimit() > new_pool_limit)
        debugs(13, DBG_IMPORTANT, "Shrinking idle mem pools to "<< std::setprecision(3) << toMB(new_pool_limit) << " MB");
#endif

    MemPools::GetInstance().setIdleLimit(new_pool_limit);
}