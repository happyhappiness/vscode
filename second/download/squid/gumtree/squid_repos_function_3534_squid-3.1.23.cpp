const refresh_t *
refreshLimits(const char *url)
{
    const refresh_t *R;

    for (R = Config.Refresh; R; R = R->next) {
        if (!regexec(&(R->compiled_pattern), url, 0, 0, 0))
            return R;
    }

    return NULL;
}