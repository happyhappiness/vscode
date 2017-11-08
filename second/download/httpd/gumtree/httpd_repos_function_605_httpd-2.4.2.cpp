static const char *process_regexp(header_entry *hdr, const char *value,
                                  apr_pool_t *pool)
{
    ap_regmatch_t pmatch[AP_MAX_REG_MATCH];
    const char *subs;
    const char *remainder;
    char *ret;
    int diffsz;
    if (ap_regexec(hdr->regex, value, AP_MAX_REG_MATCH, pmatch, 0)) {
        /* no match, nothing to do */
        return value;
    }
    subs = ap_pregsub(pool, hdr->subs, value, AP_MAX_REG_MATCH, pmatch);
    if (subs == NULL)
        return NULL;
    diffsz = strlen(subs) - (pmatch[0].rm_eo - pmatch[0].rm_so);
    if (hdr->action == hdr_edit) {
        remainder = value + pmatch[0].rm_eo;
    }
    else { /* recurse to edit multiple matches if applicable */
        remainder = process_regexp(hdr, value + pmatch[0].rm_eo, pool);
        if (remainder == NULL)
            return NULL;
        diffsz += strlen(remainder) - strlen(value + pmatch[0].rm_eo);
    }
    ret = apr_palloc(pool, strlen(value) + 1 + diffsz);
    memcpy(ret, value, pmatch[0].rm_so);
    strcpy(ret + pmatch[0].rm_so, subs);
    strcat(ret, remainder);
    return ret;
}