static const char *process_regexp(header_entry *hdr, const char *value,
                                  apr_pool_t *pool)
{
    unsigned int nmatch = 10;
    ap_regmatch_t pmatch[10];
    const char *subs;
    char *ret;
    int diffsz;
    if (ap_regexec(hdr->regex, value, nmatch, pmatch, 0)) {
        /* no match, nothing to do */
        return value;
    }
    subs = ap_pregsub(pool, hdr->subs, value, nmatch, pmatch);
    diffsz = strlen(subs) - (pmatch[0].rm_eo - pmatch[0].rm_so);
    ret = apr_palloc(pool, strlen(value) + 1 + diffsz);
    memcpy(ret, value, pmatch[0].rm_so);
    strcpy(ret + pmatch[0].rm_so, subs);
    strcat(ret, value + pmatch[0].rm_eo);
    return ret;
}