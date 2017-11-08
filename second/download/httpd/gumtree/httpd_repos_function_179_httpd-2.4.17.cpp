static void ExportRegisterHooks(apr_pool_t *p)
{
    ap_hook_log_transaction(ExportLogTransaction,NULL,NULL,APR_HOOK_MIDDLE);
}