static long memcache_lru_algorithm(long queue_clock, void *a) 
{
    cache_object_t *obj = (cache_object_t *)a;
    mem_cache_object_t *mobj = obj->vobj;
    if (mobj->priority == 0)
        mobj->priority = ((long)(queue_clock + mobj->total_refs));

    /*	
     * a 'proper' LRU function would just be
     *  mobj->priority = mobj->total_refs; 
     */
    return -1*mobj->priority;
}