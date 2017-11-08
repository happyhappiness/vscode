static const char *method_parse_config(cmd_parms *cmd, const char *require_line,
                                       const void **parsed_require_line)
{
    const char *w, *t;
    apr_int64_t *allowed = apr_pcalloc(cmd->pool, sizeof(apr_int64_t));

    t = require_line;

    while ((w = ap_getword_conf(cmd->temp_pool, &t)) && w[0]) {
        int m = ap_method_number_of(w);
        if (m == M_INVALID) {
            return apr_pstrcat(cmd->pool, "Invalid Method '", w, "'", NULL);
        }

        *allowed |= (AP_METHOD_BIT << m);
    }

    *parsed_require_line = allowed;
    return NULL;
}