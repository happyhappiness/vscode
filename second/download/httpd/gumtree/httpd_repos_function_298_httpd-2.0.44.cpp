const dav_hooks_binding *dav_get_binding_hooks(request_rec *r)
{
    return dav_get_provider(r)->binding;
}