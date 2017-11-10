static void CaseFilterInsertFilter(request_rec *r)
    {
    CaseFilterConfig *pConfig=ap_get_module_config(r->server->module_config,
                                                   &case_filter_module);

    if(!pConfig->bEnabled)
        return;

    ap_add_output_filter(s_szCaseFilterName,NULL,r,r->connection);
    }