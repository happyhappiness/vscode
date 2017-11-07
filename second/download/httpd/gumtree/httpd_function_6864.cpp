static int lua_table_set(lua_State *L)
{
    req_table_t    *t = ap_lua_check_apr_table(L, 1);
    const char     *key = luaL_checkstring(L, 2);
    const char     *val = luaL_checkstring(L, 3);
    /* Unless it's the 'notes' table, check for newline chars */
    /* t->r will be NULL in case of the connection notes, but since 
       we aren't going to check anything called 'notes', we can safely 
       disregard checking whether t->r is defined.
    */
    if (strcmp(t->n, "notes") && ap_strchr_c(val, '\n')) {
        char *badchar;
        char *replacement = apr_pstrdup(t->r->pool, val);
        badchar = replacement;
        while ( (badchar = ap_strchr(badchar, '\n')) ) {
            *badchar = ' ';
        }
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, t->r, 
                APLOGNO(02614) "mod_lua: Value for '%s' in table '%s' contains newline!",
                  key, t->n);
        apr_table_set(t->t, key, replacement);
    }
    else {
        apr_table_set(t->t, key, val);
    }
    return 0;
}