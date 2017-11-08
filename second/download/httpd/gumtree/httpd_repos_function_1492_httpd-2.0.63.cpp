static void memcache_inc_frequency(void*a)
{
    cache_object_t *obj = (cache_object_t *)a;
    mem_cache_object_t *mobj = obj->vobj;

    mobj->total_refs++;
    mobj->priority = 0;
}