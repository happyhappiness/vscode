    { NULL }
    };

static void CaseFilterRegisterHooks(apr_pool_t *p)
    {
    ap_hook_insert_filter(CaseFilterInsertFilter,NULL,NULL,APR_HOOK_MIDDLE);
    ap_register_output_filter(s_szCaseFilterName,CaseFilterOutFilter,NULL,
			      AP_FTYPE_RESOURCE);
    }

module AP_MODULE_DECLARE_DATA case_filter_module =
{
    STANDARD20_MODULE_STUFF,
