static void opt_retr(void)
{
    authn_cache_store = APR_RETRIEVE_OPTIONAL_FN(ap_authn_cache_store);
}