static module *h2_conn_mpm_module(void)
{
    check_modules(0);
    return mpm_module;
}