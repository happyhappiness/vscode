static long memcache_gdsf_algorithm(long queue_clock, void *a)
{
    cache_object_t *obj = (cache_object_t *)a;
    mem_cache_object_t *mobj = obj->vobj;

    if (mobj->priority == 0)
        mobj->priority = queue_clock -
                           (long)(mobj->total_refs*1000 / mobj->m_len);

    return mobj->priority;
}