static void eval_errf(sed_eval_t *eval, const char *fmt, ...)
{
    if (eval->errfn && eval->pool) {
        va_list args;
        const char* error;
        va_start(args, fmt);
        error = apr_pvsprintf(eval->pool, fmt, args);
        eval->errfn(eval->data, error);
        va_end(args);
    }
}