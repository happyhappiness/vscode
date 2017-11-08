static authz_section_conf* create_default_section(apr_pool_t *p)
{
    authz_section_conf *section = apr_pcalloc(p, sizeof(*section));

    section->op = AUTHZ_LOGIC_OR;

    return section;
}