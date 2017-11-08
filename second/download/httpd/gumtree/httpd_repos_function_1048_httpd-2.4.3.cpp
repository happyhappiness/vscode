static int req_parsebody(lua_State *L)
{
    apr_array_header_t          *pairs;
    apr_off_t len;
    int res;
    apr_size_t size;
    apr_size_t max_post_size;
    char *buffer;
    request_rec *r = ap_lua_check_request_rec(L, 1);
    max_post_size = (apr_size_t) luaL_optint(L, 2, MAX_STRING_LEN);
    lua_newtable(L);
    lua_newtable(L);            /* [table, table] */
    res = ap_parse_form_data(r, NULL, &pairs, -1, max_post_size);
    if (res == OK) {
        while(pairs && !apr_is_empty_array(pairs)) {
            ap_form_pair_t *pair = (ap_form_pair_t *) apr_array_pop(pairs);
            apr_brigade_length(pair->value, 1, &len);
            size = (apr_size_t) len;
            buffer = apr_palloc(r->pool, size + 1);
            apr_brigade_flatten(pair->value, buffer, &size);
            buffer[len] = 0;
            req_aprtable2luatable_cb(L, pair->name, buffer);
        }
    }
    return 2;                   /* [table<string, string>, table<string, array<string>>] */
}