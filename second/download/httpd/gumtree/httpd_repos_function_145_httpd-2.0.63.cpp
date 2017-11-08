static void ImportRegisterHooks(apr_pool_t *p)
{
    ap_hook_log_transaction(ImportLogTransaction,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_optional_fn_retrieve(ImportFnRetrieve,NULL,NULL,APR_HOOK_MIDDLE);
}