static ap_lua_vm_spec* copy_vm_spec(apr_pool_t* pool, ap_lua_vm_spec* spec) 
{
    ap_lua_vm_spec* copied_spec = apr_pcalloc(pool, sizeof(ap_lua_vm_spec));
    copied_spec->bytecode_len = spec->bytecode_len;
    copied_spec->bytecode = apr_pstrdup(pool, spec->bytecode);
    copied_spec->cb = spec->cb;
    copied_spec->cb_arg = NULL;
    copied_spec->file = apr_pstrdup(pool, spec->file);
    copied_spec->package_cpaths = apr_array_copy(pool, spec->package_cpaths);
    copied_spec->package_paths = apr_array_copy(pool, spec->package_paths);
    copied_spec->pool = pool;
    copied_spec->scope = AP_LUA_SCOPE_SERVER;
    copied_spec->codecache = spec->codecache;
    return copied_spec;
}