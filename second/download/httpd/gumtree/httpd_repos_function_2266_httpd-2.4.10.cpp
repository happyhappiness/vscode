static apr_status_t wline(sed_eval_t *eval, char *buf, int sz)
{
    apr_status_t rv = APR_SUCCESS;
    rv = eval->writefn(eval->fout, buf, sz);
    if (rv != APR_SUCCESS)
        return rv;
    rv = eval->writefn(eval->fout, "\n", 1);
    return rv;
}