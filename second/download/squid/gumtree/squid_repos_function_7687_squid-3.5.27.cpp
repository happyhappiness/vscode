bool
xstrtoui(const char *s, char **end, unsigned int *value,
         unsigned int min, unsigned int max)
{
    unsigned long v = 0;
    bool ret = xstrtoul(s, end, &v, min, max);
    if (value != NULL) {
        *value = v;

        if (v != static_cast<unsigned long>(*value)) {
            return false;
        }
    }

    return ret;
}