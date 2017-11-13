static char *xstrdup(const char *s)
{
    char *ret = strdup(s);
    if (ret == NULL) {
        fprintf(stderr, "Could not allocate memory (%"
                APR_SIZE_T_FMT " bytes)\n", strlen(s));
        exit(1);
    }
    return ret;
}