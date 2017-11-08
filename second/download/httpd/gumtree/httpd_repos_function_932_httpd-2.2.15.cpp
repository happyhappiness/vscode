static long memcache_get_priority(void*a)
{
    cache_object_t *obj = (cache_object_t *)a;
    mem_cache_object_t *mobj = obj->vobj;

    return  mobj->priority;
}