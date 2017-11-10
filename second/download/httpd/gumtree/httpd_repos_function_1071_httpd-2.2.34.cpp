static module *ap_find_loaded_module_symbol(server_rec *s, const char *modname)
{
    so_server_conf *sconf;
    ap_module_symbol_t *modi;
    ap_module_symbol_t *modie;
    int i;

    sconf = (so_server_conf *)ap_get_module_config(s->module_config,
                                                   &so_module);
    modie = (ap_module_symbol_t *)sconf->loaded_modules->elts;

    for (i = 0; i < sconf->loaded_modules->nelts; i++) {
        modi = &modie[i];
        if (modi->name != NULL && strcmp(modi->name, modname) == 0) {
            return modi->modp;
        }
    }
    return NULL;
}