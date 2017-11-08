apr_status_t sed_finalize_eval(sed_eval_t *eval, void *fout)
{
    if (eval->quitflag)
        return APR_SUCCESS;

    if (eval->finalflag)
        eval->dolflag = 1;

    eval->fout = fout;

    /* Process leftovers */
    if (eval->lspend > eval->linebuf) {
        apr_status_t rv;

        if (eval->lreadyflag) {
            eval->lreadyflag = 0;
            eval->lspend--;
        } else {
            /* Code can probably reach here when last character in output
             * buffer is not a newline.
             */
            /* Assure space for NULL */
            append_to_linebuf(eval, "");
        }

        *eval->lspend = '\0';
        rv = execute(eval);
        if (rv != APR_SUCCESS)
            return rv;
    }

    eval->quitflag = 1;

    return APR_SUCCESS;
}