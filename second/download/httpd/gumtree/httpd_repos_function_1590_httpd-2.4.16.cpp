static void ap_register_rewrite_mapfunc(char *name, rewrite_mapfunc_t *func)
{
    apr_hash_set(mapfunc_hash, name, strlen(name), (const void *)func);
}