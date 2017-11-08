static char *ftp_escape_globbingchars(apr_pool_t *p, const char *path)
{
    char *ret = apr_palloc(p, 2*strlen(path)+sizeof(""));
    char *d;
    for (d = ret; *path; ++path) {
        if (strchr(FTP_GLOBBING_CHARS, *path) != NULL)
            *d++ = '\\';
        *d++ = *path;
    }
    *d = '\0';
    return ret;
}