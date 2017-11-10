static const char *parse_int(apr_pool_t *p, const char *arg, int *val) {
    char *endptr;
    *val = strtol(arg, &endptr, 10);

    if (arg == endptr) {
        return apr_psprintf(p, "Value '%s' not numerical", endptr);
    }
    if (*endptr != '\0') {
        return apr_psprintf(p, "Cannot parse '%s'", endptr);
    }
    if (*val < 0) {
        return "Value must be non-negative";
    }
    return NULL;
}