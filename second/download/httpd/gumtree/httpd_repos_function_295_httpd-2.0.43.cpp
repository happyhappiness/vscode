const dav_hooks_locks *dav_get_lock_hooks(request_rec *r)
{
    return dav_get_provider(r)->locks;
}