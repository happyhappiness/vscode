static const char *dbd_oracle_get_name(const apr_dbd_results_t *res, int n)
{
    define_arg *val = &res->statement->out[n];

    if ((n < 0) || (n >= res->statement->nout)) {
        return NULL;
    }
    return val->name;
}