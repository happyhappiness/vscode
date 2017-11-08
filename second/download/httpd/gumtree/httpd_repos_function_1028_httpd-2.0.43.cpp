static int prefix_stat(const char *path, apr_finfo_t *sb)
{
    char curpath[LONG_STRING_LEN];
    char *cp;

    apr_cpystrn(curpath, path, sizeof(curpath));
    if (curpath[0] != '/') {
        return 0;
    }
    if ((cp = strchr(curpath+1, '/')) != NULL) {
        *cp = '\0';
    }
    if (apr_stat(sb, curpath, APR_FINFO_MIN, NULL) == APR_SUCCESS) {
        return 1;
    }
    else {
        return 0;
    }
}