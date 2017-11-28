const RefreshPattern *
refreshLimits(const char *url)
{
    const RefreshPattern *R;

    for (R = Config.Refresh; R; R = R->next) {
        if (!regexec(&(R->compiled_pattern), url, 0, 0, 0))
            return R;
    }

    return NULL;
}