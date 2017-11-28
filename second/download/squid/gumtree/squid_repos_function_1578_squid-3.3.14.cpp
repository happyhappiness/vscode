void
DelayPools::pools(unsigned short newPools)
{
    if (pools()) {
        debugs(3, DBG_CRITICAL, "parse_delay_pool_count: multiple delay_pools lines, aborting all previous delay_pools config");
        FreePools();
    }

    pools_ = newPools;

    if (pools())
        InitDelayData();
}