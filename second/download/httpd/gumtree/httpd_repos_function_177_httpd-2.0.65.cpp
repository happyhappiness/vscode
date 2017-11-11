static dav_error * dav_fs_create_lock(dav_lockdb *lockdb,
				      const dav_resource *resource,
				      dav_lock **lock)
{
    apr_datum_t key;

    key = dav_fs_build_key(lockdb->info->pool, resource);

    *lock = dav_fs_alloc_lock(lockdb,
			      key,
			      NULL);

    (*lock)->is_locknull = !resource->exists;

    return NULL;
}