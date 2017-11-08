static void memcache_set_pos(void *a, apr_ssize_t pos)
{
    cache_object_t *obj = (cache_object_t *)a;
    mem_cache_object_t *mobj = obj->vobj;

#ifdef USE_ATOMICS
    apr_atomic_set(&mobj->pos, pos);
#else
    mobj->pos = pos;
#endif    
}