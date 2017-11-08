static char *get_tempname(apr_pool_t *p)
{
    char tn[] = "htpasswd.tmp.XXXXXX";
    char *dirname;

    if (!(dirname = getenv("TEMP")) && !(dirname = getenv("TMPDIR"))) {
            dirname = P_tmpdir;
    }
    dirname = apr_psprintf(p, "%s/%s", dirname, tn);
    return dirname;
}