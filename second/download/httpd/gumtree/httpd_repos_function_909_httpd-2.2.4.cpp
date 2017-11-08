static apr_size_t memcache_cache_get_size(void*a)
{
    cache_object_t *obj = (cache_object_t *)a;
    mem_cache_object_t *mobj = obj->vobj;
    return mobj->m_len;
}