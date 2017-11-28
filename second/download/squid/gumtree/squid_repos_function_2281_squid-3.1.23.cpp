static void
redirectStateFree(redirectStateData * r)
{
    safe_free(r->orig_url);
    cbdataFree(r);
}