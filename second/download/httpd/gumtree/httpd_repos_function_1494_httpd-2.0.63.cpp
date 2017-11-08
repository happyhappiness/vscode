static apr_ssize_t memcache_get_pos(void *a)
{
    cache_object_t *obj = (cache_object_t *)a;
    mem_cache_object_t *mobj = obj->vobj;

    return apr_atomic_read(&mobj->pos);
}