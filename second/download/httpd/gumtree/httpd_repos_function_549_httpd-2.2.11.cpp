static int match_version(apr_pool_t *pool, char *version_string,
                         const char **error)
{
    ap_regex_t *compiled;
    const char *to_match;
    int rc;

    compiled = ap_pregcomp(pool, version_string, AP_REG_EXTENDED);
    if (!compiled) {
        *error = "Unable to compile regular expression";
        return 0;
    }

    *error = NULL;

    to_match = apr_psprintf(pool, "%d.%d.%d%s",
                            httpd_version.major,
                            httpd_version.minor,
                            httpd_version.patch,
                            httpd_version.add_string);

    rc = !ap_regexec(compiled, to_match, 0, NULL, 0);

    ap_pregfree(pool, compiled);
    return rc;
}