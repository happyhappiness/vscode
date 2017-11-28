void ClientDelayConfig::parsePoolRates()
{
    unsigned short pool;
    ConfigParser::ParseUShort(&pool);

    if (pool < 1 || pool > pools.size()) {
        debugs(3, DBG_CRITICAL, "parse_client_delay_pool_rates: Ignoring pool " << pool << " not in 1 .. " << pools.size());
        return;
    }

    --pool;

    pools[pool].rate = GetInteger();
    pools[pool].highwatermark = GetInteger64();
}