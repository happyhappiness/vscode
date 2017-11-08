void ssl_var_register(void)
{
    APR_REGISTER_OPTIONAL_FN(ssl_is_https);
    APR_REGISTER_OPTIONAL_FN(ssl_var_lookup);
    APR_REGISTER_OPTIONAL_FN(ssl_ext_lookup);
    return;
}