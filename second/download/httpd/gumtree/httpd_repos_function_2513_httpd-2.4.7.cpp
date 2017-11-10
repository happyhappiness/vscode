static void CaseFilterInInsertFilter(request_rec *r)
{
    CaseFilterInConfig *pConfig=ap_get_module_config(r->server->module_config,
                                                     &case_filter_in_module);
    if(!pConfig->bEnabled)
        return;

    ap_add_input_filter(s_szCaseFilterName,NULL,r,r->connection);
}