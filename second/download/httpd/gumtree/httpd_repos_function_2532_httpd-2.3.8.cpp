static void *merge_authz_core_dir_config(apr_pool_t *p,
                                         void *basev, void *newv)
{
    authz_core_dir_conf *base = (authz_core_dir_conf *)basev;
    authz_core_dir_conf *new = (authz_core_dir_conf *)newv;
    authz_core_dir_conf *conf;

    if (new->op == AUTHZ_LOGIC_OFF || !(base->section || new->section)) {
        conf = apr_pmemdup(p, new, sizeof(*new));
    }
    else {
        authz_section_conf *section;

        if (base->section) {
            if (new->section) {
                section = apr_pcalloc(p, sizeof(*section));

                section->limited =
                    base->section->limited | new->section->limited;

                section->op = new->op;

                section->first = apr_pmemdup(p, base->section,
                                             sizeof(*base->section));
                section->first->next = apr_pmemdup(p, new->section,
                                                   sizeof(*new->section));
            } else {
                section = apr_pmemdup(p, base->section,
                                      sizeof(*base->section));
            }
        }
        else {
            section = apr_pmemdup(p, new->section, sizeof(*new->section));
        }

        conf = apr_pcalloc(p, sizeof(*conf));

        conf->section = section;
        conf->op = new->op;
    }

    return (void*)conf;
}