static const RefreshPattern *
refreshUncompiledPattern(const char *pat)
{
    const RefreshPattern *R;

    for (R = Config.Refresh; R; R = R->next) {
        if (0 == strcmp(R->pattern, pat))
            return R;
    }

    return NULL;
}