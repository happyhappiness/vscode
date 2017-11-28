bool
StringToInt64(const char *s, int64_t &result, const char **p, int base)
{
    if (s) {
        char *ptr = 0;
        const int64_t h = (int64_t) strtoll(s, &ptr, base);

        if (ptr != s && ptr) {
            result = h;

            if (p)
                *p = ptr;

            return true;
        }
    }

    return false;
}