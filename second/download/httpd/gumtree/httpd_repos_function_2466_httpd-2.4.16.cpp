static const char *slotmem_filename(apr_pool_t *pool, const char *slotmemname,
                                    int persist)
{
    const char *fname;
    if (!slotmemname || strcasecmp(slotmemname, "none") == 0) {
        return NULL;
    }
    else if (slotmemname[0] != '/') {
        const char *filenm = apr_pstrcat(pool, DEFAULT_SLOTMEM_PREFIX,
                                         slotmemname, DEFAULT_SLOTMEM_SUFFIX,
                                         NULL);
        fname = ap_runtime_dir_relative(pool, filenm);
    }
    else {
        fname = slotmemname;
    }

    if (persist) {
        return apr_pstrcat(pool, fname, DEFAULT_SLOTMEM_PERSIST_SUFFIX,
                           NULL);
    }
    return fname;
}