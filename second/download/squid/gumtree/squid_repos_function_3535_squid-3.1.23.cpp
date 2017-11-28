static const refresh_t *
refreshUncompiledPattern(const char *pat)
{
    const refresh_t *R;

    for (R = Config.Refresh; R; R = R->next) {
        if (0 == strcmp(R->pattern, pat))
            return R;
    }

    return NULL;
}