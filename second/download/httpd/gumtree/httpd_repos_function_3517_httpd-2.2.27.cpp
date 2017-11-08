long safe_strtol(const char *nptr, const char **endptr, int base)
{
    long rv;

    errno = 0;

    rv = strtol(nptr, (char**)endptr, 10);

    if (errno == ERANGE) {
        return 0;
    }

    return rv; 
}