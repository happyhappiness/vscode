static int op_T(ap_expr_eval_ctx_t *ctx, const void *data, const char *arg)
{
    switch (arg[0]) {
    case '\0':
        return FALSE;
    case 'o':
    case 'O':
        return strcasecmp(arg, "off") == 0 ? FALSE : TRUE;
    case 'n':
    case 'N':
        return strcasecmp(arg, "no") == 0 ? FALSE : TRUE;
    case 'f':
    case 'F':
        return strcasecmp(arg, "false") == 0 ? FALSE : TRUE;
    case '0':
        return arg[1] == '\0' ? FALSE : TRUE;
    default:
        return TRUE;
    }
}