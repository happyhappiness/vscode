static const char *slotmem_filename(apr_pool_t *pool, const char *slotmemname)
{
    const char *fname;
    if (!slotmemname || strcasecmp(slotmemname, "none") == 0) {
        return NULL;
    }
    else if (slotmemname[0] != '/') {
        const char *filenm = apr_pstrcat(pool, DEFAULT_SLOTMEM_PREFIX,
                                       slotmemname, DEFAULT_SLOTMEM_SUFFIX, NULL);
        fname = ap_runtime_dir_relative(pool, filenm);
    }
    else {
        fname = slotmemname;
    }
    return fname;
}