static module *h2_conn_mpm_module(void) {
    check_modules();
    return mpm_module;
}