static const RefreshPattern *
refreshUncompiledPattern(const char *pat)
{
    for (auto R = Config.Refresh; R; R = R->next) {
        if (0 == strcmp(R->pattern.c_str(), pat))
            return R;
    }

    return nullptr;
}