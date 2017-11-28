bool
Rock::SwapDir::parseRateOption(char const *option, const char *value, int isaReconfig)
{
    int *storedRate;
    if (strcmp(option, "max-swap-rate") == 0)
        storedRate = &fileConfig.ioRate;
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

    const int newRate = static_cast<int>(parsedValue);

    if (newRate < 0) {
        debugs(3, DBG_CRITICAL, "FATAL: cache_dir " << path << ' ' << option << " must not be negative but is: " << newRate);
        self_destruct();
    }

    if (!isaReconfig)
        *storedRate = newRate;
    else if (*storedRate != newRate) {
        debugs(3, DBG_IMPORTANT, "WARNING: cache_dir " << path << ' ' << option
               << " cannot be changed dynamically, value left unchanged: " <<
               *storedRate);
    }

    return true;
}