const char *h2_conn_mpm_name(void)
{
    check_modules(0);
    return mpm_module? mpm_module->name : "unknown";
}