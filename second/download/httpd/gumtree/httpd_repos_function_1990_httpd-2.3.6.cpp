apr_status_t sed_eval_buffer(sed_eval_t *eval, const char *buf, int bufsz, void *fout)
{
    apr_status_t rv;

    if (eval->quitflag)
        return APR_SUCCESS;

    if (!sed_canbe_finalized(eval->commands)) {
        /* Commands were not finalized properly. */
        const char* error = sed_get_finalize_error(eval->commands, eval->pool);
        if (error) {
            eval_errf(eval, error);
            return APR_EGENERAL;
        }
    }

    eval->fout = fout;

    /* Process leftovers */
    if (bufsz && eval->lreadyflag) {
        eval->lreadyflag = 0;
        eval->lspend--;
        *eval->lspend = '\0';
        rv = execute(eval);
        if (rv != APR_SUCCESS)
            return rv;
    }

    while (bufsz) {
        char *n;
        int llen;

        n = memchr(buf, '\n', bufsz);
        if (n == NULL)
            break;

        llen = n - buf;
        if (llen == bufsz - 1) {
            /* This might be the last line; delay its processing */
            eval->lreadyflag = 1;
            break;
        }
        
        appendmem_to_linebuf(eval, buf, llen + 1);
        --eval->lspend;
        /* replace new line character with NULL */
        *eval->lspend = '\0';
        buf += (llen + 1);
        bufsz -= (llen + 1);
        rv = execute(eval);
        if (rv != APR_SUCCESS)
            return rv;
        if (eval->quitflag)
            break;
    }

    /* Save the leftovers for later */
    if (bufsz) {
        appendmem_to_linebuf(eval, buf, bufsz);
    }

    return APR_SUCCESS;
}