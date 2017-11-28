void
DelayConfig::parsePoolCount()
{
    unsigned short pools_;
    ConfigParser::ParseUShort(&pools_);
    DelayPools::pools(pools_);
}