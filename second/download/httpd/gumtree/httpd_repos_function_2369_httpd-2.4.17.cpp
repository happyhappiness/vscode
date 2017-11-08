h2_mpm_type_t h2_conn_mpm_type(void) {
    check_modules();
    return mpm_type;
}