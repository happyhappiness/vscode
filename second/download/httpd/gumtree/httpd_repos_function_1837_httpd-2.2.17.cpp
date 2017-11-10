static void CaseFilterInRegisterHooks(apr_pool_t *p)
{
    ap_hook_insert_filter(CaseFilterInInsertFilter, NULL, NULL,
                          APR_HOOK_MIDDLE);
    ap_register_input_filter(s_szCaseFilterName, CaseFilterInFilter, NULL,
                             AP_FTYPE_RESOURCE);
}