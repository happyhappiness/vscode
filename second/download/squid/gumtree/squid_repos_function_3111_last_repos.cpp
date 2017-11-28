const RefreshPattern *
refreshLimits(const char *url)
{
    for (auto R = Config.Refresh; R; R = R->next) {
        ++(R->stats.matchTests);
        if (R->pattern.match(url)) {
            ++(R->stats.matchCount);
            return R;
        }
    }

    return nullptr;
}