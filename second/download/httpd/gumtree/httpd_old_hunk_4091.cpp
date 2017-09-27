     * doubled slashes)
     */

    return urip - uri;
}

static char magic_error_value;
#define PREGSUB_ERROR      (&magic_error_value)

static char *try_alias_list(request_rec *r, apr_array_header_t *aliases,
                            int is_redir, int *status)
{
    alias_entry *entries = (alias_entry *) aliases->elts;
    ap_regmatch_t regm[AP_MAX_REG_MATCH];
