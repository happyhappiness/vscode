static void ImportRegisterHooks(apr_pool_t *p)
{
    AP_OPTIONAL_HOOK(optional_hook_test,ImportOptionalHookTestHook,NULL,
		     NULL,APR_HOOK_MIDDLE);
}