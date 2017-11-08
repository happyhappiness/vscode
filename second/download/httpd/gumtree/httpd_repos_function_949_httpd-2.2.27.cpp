static void cleanup_cache_object(cache_object_t *obj)
{
    mem_cache_object_t *mobj = obj->vobj;

    /* Cleanup the mem_cache_object_t */
    if (mobj) {
        if (mobj->m) {
            free(mobj->m);
        }
        if (mobj->type == CACHE_TYPE_FILE && mobj->fd) {
#ifdef WIN32
            CloseHandle(mobj->fd);
#else
            close(mobj->fd);
#endif
        }
        apr_pool_destroy(mobj->pool);
    }
}