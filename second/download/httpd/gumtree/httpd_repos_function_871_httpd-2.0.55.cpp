static int file_cache_xlat(request_rec *r)
{
    a_server_config *sconf;
    a_file *match;
    int res;

    sconf = ap_get_module_config(r->server->module_config, &file_cache_module);

    /* we only operate when at least one cachefile directive was used */
    if (!apr_hash_count(sconf->fileht)) {
	return DECLINED;
    }

    res = ap_core_translate(r);
    if (res != OK || !r->filename) {
	return res;
    }

    /* search the cache */
    match = (a_file *) apr_hash_get(sconf->fileht, r->filename, APR_HASH_KEY_STRING);
    if (match == NULL)
        return DECLINED;

    /* pass search results to handler */
    ap_set_module_config(r->request_config, &file_cache_module, match);

    /* shortcircuit the get_path_info() stat() calls and stuff */
    r->finfo = match->finfo;
    return OK;
}