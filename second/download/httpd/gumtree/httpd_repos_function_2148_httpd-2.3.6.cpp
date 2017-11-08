static const char *store_filename(apr_pool_t *pool, const char *slotmemname)
{
    const char *storename;
    const char *fname;
    if (strcmp(slotmemname, "anonymous") == 0)
        fname = ap_server_root_relative(pool, "logs/anonymous");
    else if (slotmemname[0] == ':') {
        const char *tmpname;
        tmpname = apr_pstrcat(pool, "logs/", &slotmemname[1], NULL);
        fname = ap_server_root_relative(pool, tmpname);
    }
    else {
        fname = slotmemname;
    }
    storename = apr_pstrcat(pool, fname, ".slotmem", NULL);
    return storename;
}