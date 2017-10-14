static int authz_core_check_section(apr_pool_t *p, server_rec *s,
                                    authz_section_conf *section, int is_conf)
{
    authz_section_conf *prev = NULL;
    authz_section_conf *child = section->first;
    int ret = !OK;

    while (child) {
        if (child->first) {
            if (authz_core_check_section(p, s, child, 0) != OK) {
                return !OK;
            }

            if (child->negate && child->op != section->op) {
                authz_section_conf *next = child->next;

                /* avoid one level of recursion when De Morgan permits */
                child = child->first;

                if (prev) {
                    prev->next = child;
                }
                else {
                    section->first = child;
                }

                do {
                    child->negate = !child->negate;
                } while (child->next && (child = child->next));

                child->next = next;
            }
        }

        prev = child;
        child = child->next;
    }

    child = section->first;

    while (child) {
        if (!child->negate) {
            ret = OK;
            break;
        }

        child = child->next;
    }

    if (ret != OK) {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, APR_SUCCESS, s, APLOGNO(01624)
                     "%s directive contains only negative authorization directives",
                     is_conf ? "<Directory>, <Location>, or similar"
                             : format_authz_command(p, section));
    }

    return ret;
}