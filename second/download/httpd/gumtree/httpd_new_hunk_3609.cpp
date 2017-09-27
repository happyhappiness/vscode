    nscript->replen = strlen(to);
    nscript->flatten = flatten;

    return NULL;
}

#define KBYTE         1024
#define MBYTE         1048576
#define GBYTE         1073741824

static const char *set_max_line_length(cmd_parms *cmd, void *cfg, const char *arg)
{
    subst_dir_conf *dcfg = (subst_dir_conf *)cfg;
    apr_off_t max;
    char *end;
    apr_status_t rv;

    rv = apr_strtoff(&max, arg, &end, 10);
    if (rv == APR_SUCCESS) {
        if ((*end == 'K' || *end == 'k') && !end[1]) {
            max *= KBYTE;
        }
        else if ((*end == 'M' || *end == 'm') && !end[1]) {
            max *= MBYTE;
        }
        else if ((*end == 'G' || *end == 'g') && !end[1]) {
            max *= GBYTE;
        }
        else if (*end && /* neither empty nor [Bb] */
                 ((*end != 'B' && *end != 'b') || end[1])) {
            rv = APR_EGENERAL;
        }
    }

    if (rv != APR_SUCCESS || max < 0)
    {
        return "SubstituteMaxLineLength must be a non-negative integer optionally "
               "suffixed with 'b', 'k', 'm' or 'g'.";
    }
    dcfg->max_line_length = (apr_size_t)max;
    dcfg->max_line_length_set = 1;
    return NULL;
}

#define PROTO_FLAGS AP_FILTER_PROTO_CHANGE|AP_FILTER_PROTO_CHANGE_LENGTH
static void register_hooks(apr_pool_t *pool)
{
    ap_register_output_filter(substitute_filter_name, substitute_filter,
                              NULL, AP_FTYPE_RESOURCE);
}

static const command_rec substitute_cmds[] = {
    AP_INIT_TAKE1("Substitute", set_pattern, NULL, OR_FILEINFO,
                  "Pattern to filter the response content (s/foo/bar/[inf])"),
    AP_INIT_TAKE1("SubstituteMaxLineLength", set_max_line_length, NULL, OR_FILEINFO,
                  "Maximum line length"),
    {NULL}
};

AP_DECLARE_MODULE(substitute) = {
    STANDARD20_MODULE_STUFF,
    create_substitute_dcfg,     /* dir config creater */
