static const char *dbd_statement(apr_pool_t *pool,
                                 apr_dbd_prepared_t *stmt,
                                 int nargs, const char **args)
{
    int i;
    int len;
    const char *var;
    char *ret;
    const char *p_in;
    char *p_out;
    char *q;
   
    /* compute upper bound on length (since untaint shrinks) */
    len  = strlen(stmt->fmt) +1;
    for (i=0; i<nargs; ++i) {
        len += strlen(args[i]) - 2;
    }
    i = 0;
    p_in = stmt->fmt;
    p_out = ret = apr_palloc(pool, len);
    /* FIXME silly bug - this'll catch %%s */
    while (q = strstr(p_in, "%s"), q != NULL) {
        len = q-p_in;
        strncpy(p_out, p_in, len);
        p_in += len;
        p_out += len;
        var = dbd_untaint(pool, stmt->taint[i], args[i]);
        len = strlen(var);
        strncpy(p_out, var, len);
        p_in += 2;
        p_out += len;
        ++i;
    }
    strcpy(p_out, p_in);
    return ret;
}