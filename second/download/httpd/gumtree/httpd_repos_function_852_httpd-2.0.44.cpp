void ssl_var_register(void)
{
    APR_REGISTER_OPTIONAL_FN(ssl_var_lookup);
    return;
}