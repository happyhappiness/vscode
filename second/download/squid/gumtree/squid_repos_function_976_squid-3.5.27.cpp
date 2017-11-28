bool
StringToInt(const char *s, int &result, const char **p, int base)
{
    if (s) {
        char *ptr = 0;
        const int h = (int) strtol(s, &ptr, base);

        if (ptr != s && ptr) {
            result = h;

            if (p)
                *p = ptr;

            return true;
        }
    }

    return false;
}