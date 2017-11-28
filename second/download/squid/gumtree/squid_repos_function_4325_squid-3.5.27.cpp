time_t Adaptation::Icap::Config::connect_timeout(bool bypassable) const
{
    if (connect_timeout_raw > 0)
        return connect_timeout_raw; // explicitly configured

    return bypassable ? ::Config.Timeout.peer_connect : ::Config.Timeout.connect;
}