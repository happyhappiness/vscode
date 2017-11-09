static void munge_path(lua_State *L,
                       const char *field,
                       const char *sub_pat,
                       const char *rep_pat,
                       apr_pool_t *pool,
                       apr_array_header_t *paths,
                       const char *file)
{
    const char *current;
    const char *parent_dir;
    const char *pattern;
    const char *modified;
    char *part;

    lua_getglobal(L, "package");
    lua_getfield(L, -1, field);
    
    current = lua_tostring(L, -1);

    parent_dir = ap_make_dirstr_parent(pool, file);
 
    pattern = apr_pstrcat(pool, parent_dir, sub_pat, NULL);

    luaL_gsub(L, current, rep_pat, pattern);
    lua_setfield(L, -3, field);
    lua_getfield(L, -2, field);
    modified = lua_tostring(L, -1);


    lua_pop(L, 2);

    part = apr_pstrcat(pool, modified, ";", apr_array_pstrcat(pool, paths, ';'),
                       NULL);

    lua_pushstring(L, part);
    lua_setfield(L, -2, field);
    lua_pop(L, 1);              /* pop "package" off the stack     */
}