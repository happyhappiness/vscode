    nscript->replen = strlen(to);
    nscript->flatten = flatten;

    return NULL;
}

#define PROTO_FLAGS AP_FILTER_PROTO_CHANGE|AP_FILTER_PROTO_CHANGE_LENGTH
static void register_hooks(apr_pool_t *pool)
{
    ap_register_output_filter(substitute_filter_name, substitute_filter,
                              NULL, AP_FTYPE_RESOURCE);
}

static const command_rec substitute_cmds[] = {
    AP_INIT_TAKE1("Substitute", set_pattern, NULL, OR_ALL,
                  "Pattern to filter the response content (s/foo/bar/[inf])"),
    {NULL}
};

AP_DECLARE_MODULE(substitute) = {
    STANDARD20_MODULE_STUFF,
    create_substitute_dcfg,     /* dir config creater */
