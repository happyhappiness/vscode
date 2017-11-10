static void register_hooks(apr_pool_t * p)
{
    ap_hook_session_encode(session_crypto_encode, NULL, NULL, APR_HOOK_LAST);
    ap_hook_session_decode(session_crypto_decode, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_post_config(session_crypto_init, NULL, NULL, APR_HOOK_LAST);
}