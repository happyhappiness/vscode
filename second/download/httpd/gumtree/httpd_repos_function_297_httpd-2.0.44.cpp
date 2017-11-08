const dav_hooks_vsn *dav_get_vsn_hooks(request_rec *r)
{
    return dav_get_provider(r)->vsn;
}