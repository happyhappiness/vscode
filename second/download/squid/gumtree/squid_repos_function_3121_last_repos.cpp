time_t
getMaxAge(const char *url)
{
    const RefreshPattern *R;
    debugs(22, 3, "getMaxAge: '" << url << "'");

    if ((R = refreshLimits(url)))
        return R->max;
    else
        return REFRESH_DEFAULT_MAX;
}