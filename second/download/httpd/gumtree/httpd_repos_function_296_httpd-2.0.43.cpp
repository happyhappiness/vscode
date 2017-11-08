const dav_hooks_propdb *dav_get_propdb_hooks(request_rec *r)
{
    return dav_get_provider(r)->propdb;
}