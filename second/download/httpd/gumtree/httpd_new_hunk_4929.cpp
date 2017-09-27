    }

    fprintf(stderr, "Total #records : %d\n", i);
    return APR_SUCCESS;
}

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

static apr_status_t htdbm_valid_username(htdbm_t *htdbm)
{
    if (!htdbm->username || (strlen(htdbm->username) > 64) || (strlen(htdbm->username) < 1)) {
        fprintf(stderr, "Invalid username length\n");
