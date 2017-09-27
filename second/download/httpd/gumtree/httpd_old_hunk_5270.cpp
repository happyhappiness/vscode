    lua_pop(L, 1);

    rft = apr_hash_get(dispatch, name, APR_HASH_KEY_STRING);
    if (rft) {
        switch (rft->type) {
        case APL_REQ_FUNTYPE_TABLE:{
                apr_table_t *rs;
                req_field_apr_table_f func = (req_field_apr_table_f)rft->fun;
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01486)
                              "request_rec->dispatching %s -> apr table",
                              name);
                rs = (*func)(r);
                ap_lua_push_apr_table(L, rs);
