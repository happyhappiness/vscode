    rft = apr_hash_get(dispatch, name, APR_HASH_KEY_STRING);
    if (rft) {
        switch (rft->type) {
        case APL_REQ_FUNTYPE_TABLE:{
                apr_table_t *rs;
                req_field_apr_table_f func = (req_field_apr_table_f)rft->fun;
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "request_rec->dispatching %s -> apr table",
                              name);
                rs = (*func)(r);
                ap_lua_push_apr_table(L, rs);          
                return 1;
            }

        case APL_REQ_FUNTYPE_LUACFUN:{
                lua_CFunction func = (lua_CFunction)rft->fun;
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "request_rec->dispatching %s -> lua_CFunction",
                              name);
                lua_pushcfunction(L, func);
                return 1;
            }
        case APL_REQ_FUNTYPE_STRING:{
                req_field_string_f func = (req_field_string_f)rft->fun;
                char *rs;
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "request_rec->dispatching %s -> string", name);
                rs = (*func) (r);
                lua_pushstring(L, rs);
                return 1;
            }
        case APL_REQ_FUNTYPE_INT:{
                req_field_int_f func = (req_field_int_f)rft->fun;
                int rs;
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "request_rec->dispatching %s -> int", name);
                rs = (*func) (r);
                lua_pushnumber(L, rs);
                return 1;
            }
        case APL_REQ_FUNTYPE_BOOLEAN:{
                req_field_int_f func = (req_field_int_f)rft->fun;
                int rs;
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "request_rec->dispatching %s -> boolean", name);
                rs = (*func) (r);
                lua_pushboolean(L, rs);
                return 1;
            }
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "nothing for %s", name);
    return 0;
}

/* helper function for the logging functions below */
static int req_log_at(lua_State *L, int level)
{
