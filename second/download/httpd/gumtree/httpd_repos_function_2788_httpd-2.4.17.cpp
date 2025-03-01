static int slotmem_filenames(apr_pool_t *pool,
                             const char *slotname,
                             const char **filename,
                             const char **persistname)
{
    const char *fname = NULL, *pname = NULL;

    if (slotname && *slotname && strcasecmp(slotname, "none") != 0) {
        if (slotname[0] != '/') {
#if !SLOTMEM_UNLINK_SEMANTIC
            /* Each generation needs its own file name. */
            int generation = 0;
            ap_mpm_query(AP_MPMQ_GENERATION, &generation);
            fname = apr_psprintf(pool, "%s%s_%x%s", DEFAULT_SLOTMEM_PREFIX,
                                 slotname, generation, DEFAULT_SLOTMEM_SUFFIX);
#else
            /* Reuse the same file name for each generation. */
            fname = apr_pstrcat(pool, DEFAULT_SLOTMEM_PREFIX,
                                slotname, DEFAULT_SLOTMEM_SUFFIX,
                                NULL);
#endif
            fname = ap_runtime_dir_relative(pool, fname);
        }
        else {
            /* Don't mangle the file name if given an absolute path, it's
             * up to the caller to provide a unique name when necessary.
             */
            fname = slotname;
        }

        if (persistname) {
            /* Persisted file names are immutable... */
#if !SLOTMEM_UNLINK_SEMANTIC
            if (slotname[0] != '/') {
                pname = apr_pstrcat(pool, DEFAULT_SLOTMEM_PREFIX,
                                    slotname, DEFAULT_SLOTMEM_SUFFIX,
                                    DEFAULT_SLOTMEM_PERSIST_SUFFIX,
                                    NULL);
                pname = ap_runtime_dir_relative(pool, pname);
            }
            else
#endif
            pname = apr_pstrcat(pool, fname,
                                DEFAULT_SLOTMEM_PERSIST_SUFFIX,
                                NULL);
        }
    }

    *filename = fname;
    if (persistname) {
        *persistname = pname;
    }
    return (fname != NULL);
}