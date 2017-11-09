static const char* format_authz_command(apr_pool_t *p,
                                        authz_section_conf *section)
{
    return (section->provider
            ? apr_pstrcat(p, "Require ", (section->negate ? "not " : ""),
                          section->provider_name, " ",
                          section->provider_args, NULL)
            : apr_pstrcat(p, section->is_merged ? "AuthMerging " : "<Require",
                          ((section->op == AUTHZ_LOGIC_AND)
                           ? (section->negate ? "NotAll" : "All")
                           : (section->negate ? "None" : "Any")),
                          section->is_merged ? "" : ">", NULL));
}