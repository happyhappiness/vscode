static const char *ftp_escape_globbingchars(apr_pool_t *p, const char *path, proxy_ftp_dir_conf *dconf)
{
    char *ret;
    char *d;
    
    if (!dconf->ftp_escape_wildcards) {
        return path;
    }

    ret = apr_palloc(p, 2*strlen(path)+sizeof(""));
    for (d = ret; *path; ++path) {
        if (strchr(FTP_GLOBBING_CHARS, *path) != NULL)
            *d++ = '\\';
        *d++ = *path;
    }
    *d = '\0';
    return ret;
}