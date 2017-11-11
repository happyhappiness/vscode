apr_status_t sed_reset_eval(sed_eval_t *eval, sed_commands_t *commands, sed_err_fn_t *errfn, void *data)
{
    int i;

    eval->errfn = errfn;
    eval->data = data;

    eval->commands = commands;

    eval->lnum = 0;
    eval->fout = NULL;

    if (eval->linebuf == NULL) {
        eval->lsize = INIT_BUF_SIZE;
        eval->linebuf = apr_pcalloc(eval->pool, eval->lsize);
    }
    if (eval->holdbuf == NULL) {
        eval->hsize = INIT_BUF_SIZE;
        eval->holdbuf = apr_pcalloc(eval->pool, eval->hsize);
    }
    if (eval->genbuf == NULL) {
        eval->gsize = INIT_BUF_SIZE;
        eval->genbuf = apr_pcalloc(eval->pool, eval->gsize);
    }
    eval->lspend = eval->linebuf;
    eval->hspend = eval->holdbuf;
    eval->lcomend = &eval->genbuf[71];

    for (i = 0; i < sizeof(eval->abuf) / sizeof(eval->abuf[0]); i++)
        eval->abuf[i] = NULL;
    eval->aptr = eval->abuf;
    eval->pending = NULL;
    eval->inar = apr_pcalloc(eval->pool, commands->nrep * sizeof(unsigned char));
    eval->nrep = commands->nrep;

    eval->dolflag = 0;
    eval->sflag = 0;
    eval->jflag = 0;
    eval->delflag = 0;
    eval->lreadyflag = 0;
    eval->quitflag = 0;
    eval->finalflag = 1; /* assume we're evaluating only one file/stream */
    eval->numpass = 0;
    eval->nullmatch = 0;
    eval->col = 0;

    for (i = 0; i < commands->nfiles; i++) {
        const char* filename = commands->fname[i];
        if (apr_file_open(&eval->fcode[i], filename,
                          APR_WRITE | APR_CREATE, APR_OS_DEFAULT,
                          eval->pool) != APR_SUCCESS) {
            eval_errf(eval, SEDERR_COMES, filename);
            return APR_EGENERAL;
        }
    }

    return APR_SUCCESS;
}