static int htdbm_make(htdbm_t *htdbm)
{
    char cpw[MAX_STRING_LEN];
    int ret;

    htdbm->ctx.out = cpw;
    htdbm->ctx.out_len = sizeof(cpw);
    ret = mkhash(&htdbm->ctx);
    if (ret != 0) {
        fprintf(stderr, "Error: %s\n", htdbm->ctx.errstr);
        return ret;
    }
    htdbm->ctx.passwd = apr_pstrdup(htdbm->ctx.pool, cpw);
    return 0;
}