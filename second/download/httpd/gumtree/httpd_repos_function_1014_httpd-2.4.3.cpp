static void *merge_dir_config(apr_pool_t *p, void *basev, void *overridesv)
{
    ap_lua_dir_cfg *a, *base, *overrides;

    a         = (ap_lua_dir_cfg *)apr_pcalloc(p, sizeof(ap_lua_dir_cfg));
    base      = (ap_lua_dir_cfg*)basev;
    overrides = (ap_lua_dir_cfg*)overridesv;

    a->pool = overrides->pool;
    a->dir = apr_pstrdup(p, overrides->dir);

    a->vm_scope = (overrides->vm_scope == AP_LUA_SCOPE_UNSET) ? base->vm_scope: overrides->vm_scope;
    a->inherit = (overrides->inherit== AP_LUA_INHERIT_UNSET) ? base->inherit : overrides->inherit;

    if (a->inherit == AP_LUA_INHERIT_UNSET || a->inherit == AP_LUA_INHERIT_PARENT_FIRST) { 
        a->package_paths = apr_array_append(p, base->package_paths, overrides->package_paths);
        a->package_cpaths = apr_array_append(p, base->package_cpaths, overrides->package_cpaths);
        a->mapped_handlers = apr_array_append(p, base->mapped_handlers, overrides->mapped_handlers);
        a->hooks = apr_hash_merge(p, overrides->hooks, base->hooks, overlay_hook_specs, NULL);
    }
    else if (a->inherit == AP_LUA_INHERIT_PARENT_LAST) { 
        a->package_paths = apr_array_append(p, overrides->package_paths, base->package_paths);
        a->package_cpaths = apr_array_append(p, overrides->package_cpaths, base->package_cpaths);
        a->mapped_handlers = apr_array_append(p, overrides->mapped_handlers, base->mapped_handlers);
        a->hooks = apr_hash_merge(p, base->hooks, overrides->hooks, overlay_hook_specs, NULL);
    }
    else { 
        a->package_paths = overrides->package_paths;
        a->package_cpaths = overrides->package_cpaths;
        a->mapped_handlers= overrides->mapped_handlers;
        a->hooks= overrides->hooks;
    }

    return a;
}