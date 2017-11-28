void ClientDelayConfig::parsePoolCount()
{
    if (pools.size()) {
        debugs(3, DBG_CRITICAL, "parse_client_delay_pool_count: multiple client_delay_pools lines, aborting all previous client_delay_pools config");
        clean();
    }
    unsigned short pools_;
    ConfigParser::ParseUShort(&pools_);
    for (int i = 0; i < pools_; ++i) {
        pools.push_back(ClientDelayPool());
    }
}