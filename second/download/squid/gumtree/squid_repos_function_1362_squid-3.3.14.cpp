void
DelayConfig::parsePoolAccess(ConfigParser &parser)
{
    unsigned short pool;

    ConfigParser::ParseUShort(&pool);

    if (pool < 1 || pool > DelayPools::pools()) {
        debugs(3, DBG_CRITICAL, "parse_delay_pool_rates: Ignoring pool " << pool << " not in 1 .. " << DelayPools::pools());
        return;
    }

    --pool;
    aclParseAccessLine(parser, &DelayPools::delay_data[pool].access);
}