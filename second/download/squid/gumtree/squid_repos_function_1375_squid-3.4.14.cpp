void
DelayConfig::parsePoolClass()
{
    unsigned short pool;

    ConfigParser::ParseUShort(&pool);

    if (pool < 1 || pool > DelayPools::pools()) {
        debugs(3, DBG_CRITICAL, "parse_delay_pool_class: Ignoring pool " << pool << " not in 1 .. " << DelayPools::pools());
        return;
    }

    unsigned short delay_class_;
    ConfigParser::ParseUShort(&delay_class_);

    if (delay_class_ < 1 || delay_class_ > 5) {
        debugs(3, DBG_CRITICAL, "parse_delay_pool_class: Ignoring pool " << pool << " class " << delay_class_ << " not in 1 .. 5");
        return;
    }

    --pool;

    DelayPools::delay_data[pool].createPool(delay_class_);
}