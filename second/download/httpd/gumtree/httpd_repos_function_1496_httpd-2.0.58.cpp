static void cleanup_cache_object(cache_object_t *obj)
{
    mem_cache_object_t *mobj = obj->vobj;

    /* TODO:
     * We desperately need a more efficient way of allocating objects. We're
     * making way too many malloc calls to create a fully populated 
     * cache object...
     */

    /* Cleanup the cache_object_t */
    if (obj->key) {
        free(obj->key);
    }
    if (obj->info.content_type) {
        free(obj->info.content_type);
    }
    if (obj->info.etag) {
        free(obj->info.etag);
    }
    if (obj->info.lastmods) {
        free(obj->info.lastmods);
    }
    if (obj->info.filename) {
        free(obj->info.filename);
    }

    free(obj);
    
    /* Cleanup the mem_cache_object_t */
    if (mobj) {
        if (mobj->type == CACHE_TYPE_HEAP && mobj->m) {
            free(mobj->m);
        }
        if (mobj->type == CACHE_TYPE_FILE && mobj->fd) {
#ifdef WIN32
            CloseHandle(mobj->fd);
#else
            close(mobj->fd);
#endif
        }
        if (mobj->header_out) {
            if (mobj->header_out[0].hdr) 
                free(mobj->header_out[0].hdr);
            free(mobj->header_out);
        }
        if (mobj->err_header_out) {
            if (mobj->err_header_out[0].hdr) 
                free(mobj->err_header_out[0].hdr);
            free(mobj->err_header_out);
        }
        if (mobj->subprocess_env) {
            if (mobj->subprocess_env[0].hdr) 
                free(mobj->subprocess_env[0].hdr);
            free(mobj->subprocess_env);
        }
        if (mobj->notes) {
            if (mobj->notes[0].hdr) 
                free(mobj->notes[0].hdr);
            free(mobj->notes);
        }
        if (mobj->req_hdrs) {
            if (mobj->req_hdrs[0].hdr)
                free(mobj->req_hdrs[0].hdr);
            free(mobj->req_hdrs);
        }
        free(mobj);
    }
}