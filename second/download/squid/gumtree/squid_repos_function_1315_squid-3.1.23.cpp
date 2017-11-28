void
DelayConfig::parsePoolRates()
{
    unsigned short pool;
    ConfigParser::ParseUShort(&pool);

    if (pool < 1 || pool > DelayPools::pools()) {
        debugs(3, 0, "parse_delay_pool_rates: Ignoring pool " << pool << " not in 1 .. " << DelayPools::pools());
        return;
    }

    pool--;

    if (!DelayPools::delay_data[pool].theComposite().getRaw()) {
        debugs(3, 0, "parse_delay_pool_rates: Ignoring pool " << pool + 1 << " attempt to set rates with class not set");
        return;
    }

    DelayPools::delay_data[pool].parse();
}