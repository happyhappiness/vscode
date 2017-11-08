static int core_expr_lookup(ap_expr_lookup_parms *parms)
{
    switch (parms->type) {
    case AP_EXPR_FUNC_VAR: {
            const struct expr_provider_multi *prov = var_providers;
            while (prov->func) {
                const char **name = prov->names;
                while (*name) {
                    if (strcasecmp(*name, parms->name) == 0) {
                        *parms->func = prov->func;
                        *parms->data = name;
                        return OK;
                    }
                    name++;
                }
                prov++;
            }
        }
        break;
    case AP_EXPR_FUNC_STRING:
    case AP_EXPR_FUNC_OP_UNARY:
    case AP_EXPR_FUNC_OP_BINARY: {
            const struct expr_provider_single *prov;
            switch (parms->type) {
            case AP_EXPR_FUNC_STRING:
                prov = string_func_providers;
                break;
            case AP_EXPR_FUNC_OP_UNARY:
                prov = unary_op_providers;
                break;
            case AP_EXPR_FUNC_OP_BINARY:
                prov = binary_op_providers;
                break;
            default:
                ap_assert(0);
            }
            while (prov->func) {
                int match;
                if (parms->type == AP_EXPR_FUNC_OP_UNARY)
                    match = !strcmp(prov->name, parms->name);
                else
                    match = !strcasecmp(prov->name, parms->name);
                if (match) {
                    if ((parms->flags & AP_EXPR_FLAG_RESTRICTED)
                        && prov->restricted) {
                        *parms->err =
                            apr_psprintf(parms->ptemp,
                                         "%s%s not available in restricted context",
                                         (parms->type == AP_EXPR_FUNC_STRING) ? "" : "-",
                                         prov->name);
                        return !OK;
                    }
                    *parms->func = prov->func;
                    if (prov->arg_parsing_func) {
                        return prov->arg_parsing_func(parms);
                    }
                    else {
                        *parms->data = prov->name;
                        return OK;
                    }
                }
                prov++;
            }
        }
        break;
    default:
        break;
    }
    return DECLINED;
}