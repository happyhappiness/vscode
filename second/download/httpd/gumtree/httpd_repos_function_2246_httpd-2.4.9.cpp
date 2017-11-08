apr_status_t sed_eval_file(sed_eval_t *eval, apr_file_t *fin, void *fout)
{
    for (;;) {
        char buf[1024];
        apr_size_t read_bytes = 0;

        read_bytes = sizeof(buf);
        if (apr_file_read(fin, buf, &read_bytes) != APR_SUCCESS)
            break;

        if (sed_eval_buffer(eval, buf, read_bytes, fout) != APR_SUCCESS)
            return APR_EGENERAL;

        if (eval->quitflag)
            return APR_SUCCESS;
    }

    return sed_finalize_eval(eval, fout);
}