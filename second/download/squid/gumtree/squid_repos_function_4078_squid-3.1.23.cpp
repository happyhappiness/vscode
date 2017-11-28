time_t Adaptation::Icap::Config::io_timeout(bool) const
{
    if (io_timeout_raw > 0)
        return io_timeout_raw; // explicitly configured
    // TODO: provide a different default for an ICAP transaction that
    // can still be bypassed
    return ::Config.Timeout.read;
}