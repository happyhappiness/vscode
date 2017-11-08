static int remove_entity(cache_handle_t *h)
{
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;

    close_disk_cache_fd(&(dobj->hdrs));
    close_disk_cache_fd(&(dobj->vary));
    close_disk_cache_fd(&(dobj->data));

    /* Null out the cache object pointer so next time we start from scratch  */
    h->cache_obj = NULL;
    return OK;
}