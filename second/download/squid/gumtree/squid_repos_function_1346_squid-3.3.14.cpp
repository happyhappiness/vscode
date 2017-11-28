HelperChildConfig &
HelperChildConfig::updateLimits(const HelperChildConfig &rhs)
{
    // Copy the limits only.
    // Preserve the local state values (n_running and n_active)
    n_max = rhs.n_max;
    n_startup = rhs.n_startup;
    n_idle = rhs.n_idle;
    concurrency = rhs.concurrency;
    return *this;
}