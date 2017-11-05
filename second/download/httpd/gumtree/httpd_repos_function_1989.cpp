apr_status_t sed_init_eval(sed_eval_t *eval, sed_commands_t *commands, sed_err_fn_t *errfn, void *data, sed_write_fn_t *writefn, apr_pool_t* p)
{
    memset(eval, 0, sizeof(*eval));
    eval->pool = p;
    eval->writefn = writefn;
    return sed_reset_eval(eval, commands, errfn, data);
}