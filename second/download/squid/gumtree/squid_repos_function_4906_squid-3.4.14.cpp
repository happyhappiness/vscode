bool
Rock::SwapDir::parseTimeOption(char const *option, const char *value, int reconfig)
{
    // TODO: ::SwapDir or, better, Config should provide time-parsing routines,
    // including time unit handling. Same for size.

    time_msec_t *storedTime;
    if (strcmp(option, "swap-timeout") == 0)
        storedTime = &fileConfig.ioTimeout;
    else
        return false;

    if (!value)
        self_destruct();

    // TODO: handle time units and detect parsing errors better
    const int64_t parsedValue = strtoll(value, NULL, 10);
    if (parsedValue < 0) {
        debugs(3, DBG_CRITICAL, "FATAL: cache_dir " << path << ' ' << option << " must not be negative but is: " << parsedValue);
        self_destruct();
    }

    const time_msec_t newTime = static_cast<time_msec_t>(parsedValue);

    if (!reconfig)
        *storedTime = newTime;
    else if (*storedTime != newTime) {
        debugs(3, DBG_IMPORTANT, "WARNING: cache_dir " << path << ' ' << option
               << " cannot be changed dynamically, value left unchanged: " <<
               *storedTime);
    }

    return true;
}