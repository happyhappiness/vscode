void sed_destroy_eval(sed_eval_t *eval)
{
    int i;
    /* eval->linebuf, eval->holdbuf, eval->genbuf and eval->inar are allocated
     * on pool. It will be freed when pool will be freed */
    for (i = 0; i < eval->commands->nfiles; i++) {
        if (eval->fcode[i] != NULL) {
            apr_file_close(eval->fcode[i]);
            eval->fcode[i] = NULL;
        }
    }
}