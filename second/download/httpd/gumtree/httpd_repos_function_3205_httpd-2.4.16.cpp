static int expr_lookup_not_found(ap_expr_lookup_parms *parms)
{
    const char *type;
    const char *prefix = "";

    switch (parms->type) {
    case AP_EXPR_FUNC_VAR:
        type = "Variable";
        break;
    case AP_EXPR_FUNC_STRING:
        type = "Function";
        break;
    case AP_EXPR_FUNC_LIST:
        type = "List-returning function";
        break;
    case AP_EXPR_FUNC_OP_UNARY:
        type = "Unary operator";
        break;
    case AP_EXPR_FUNC_OP_BINARY:
        type = "Binary operator";
        break;
    default:
        *parms->err = "Inavalid expression type in expr_lookup";
        return !OK;
    }
    if (   parms->type == AP_EXPR_FUNC_OP_UNARY
        || parms->type == AP_EXPR_FUNC_OP_BINARY) {
        prefix = "-";
    }
    *parms->err = apr_psprintf(parms->ptemp, "%s '%s%s' does not exist", type,
                               prefix, parms->name);
    return !OK;
}