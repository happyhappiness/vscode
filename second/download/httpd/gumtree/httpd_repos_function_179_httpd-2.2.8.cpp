static dav_error * dav_generic_create_lock(dav_lockdb *lockdb,
                                      const dav_resource *resource,
                                      dav_lock **lock)
{
    apr_datum_t key;

    key = dav_generic_build_key(lockdb->info->pool, resource);

    *lock = dav_generic_alloc_lock(lockdb, key, NULL);

    (*lock)->is_locknull = !resource->exists;

    return NULL;
}