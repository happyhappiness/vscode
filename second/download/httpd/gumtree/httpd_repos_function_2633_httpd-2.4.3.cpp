static void *merge_authz_core_dir_config(apr_pool_t *p,
                                         void *basev, void *newv)
{
    authz_core_dir_conf *base = (authz_core_dir_conf *)basev;
    authz_core_dir_conf *new = (authz_core_dir_conf *)newv;
    authz_core_dir_conf *conf;

    if (new->op == AUTHZ_LOGIC_UNSET && !new->section && base->section ) {
        /* Only authz_forbidden_on_fail has been set in new. Don't treat
         * it as a new auth config w.r.t. AuthMerging */
        conf = apr_pmemdup(p, base, sizeof(*base));
    }
    else if (new->op == AUTHZ_LOGIC_OFF || new->op == AUTHZ_LOGIC_UNSET ||
             !(base->section || new->section)) {
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
                section->is_merged = 1;

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

    if (new->authz_forbidden_on_fail == UNSET)
        conf->authz_forbidden_on_fail = base->authz_forbidden_on_fail;
    else
        conf->authz_forbidden_on_fail = new->authz_forbidden_on_fail;

    return (void*)conf;
}