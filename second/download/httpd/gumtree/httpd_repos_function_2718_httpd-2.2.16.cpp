apr_status_t apu_dso_load(apr_dso_handle_sym_t *dsoptr,
                          const char *module,
                          const char *modsym,
                          apr_pool_t *pool)
{
    apr_dso_handle_t *dlhandle = NULL;
    char *pathlist;
    char path[APR_PATH_MAX + 1];
    apr_array_header_t *paths;
    apr_pool_t *global;
    apr_status_t rv = APR_EDSOOPEN;
    char *eos = NULL;
    int i;

    *dsoptr = apr_hash_get(dsos, module, APR_HASH_KEY_STRING);
    if (*dsoptr) {
        return APR_EINIT;
    }

    /* The driver DSO must have exactly the same lifetime as the
     * drivers hash table; ignore the passed-in pool */
    global = apr_hash_pool_get(dsos);

    /* Retrieve our path search list or prepare for a single search */
    if ((apr_env_get(&pathlist, APR_DSOPATH, pool) != APR_SUCCESS)
          || (apr_filepath_list_split(&paths, pathlist, pool) != APR_SUCCESS))
        paths = apr_array_make(pool, 1, sizeof(char*));

#if defined(APU_DSO_LIBDIR)
    /* Always search our prefix path, but on some platforms such as
     * win32 this may be left undefined
     */
    (*((char **)apr_array_push(paths))) = APU_DSO_LIBDIR;
#endif

    for (i = 0; i < paths->nelts; ++i)
    {
#if defined(WIN32)
        /* Use win32 dso search semantics and attempt to
         * load the relative lib on the first pass.
         */
        if (!eos) {
            eos = path;
            --i;
        }
        else
#endif
        {
            eos = apr_cpystrn(path, ((char**)paths->elts)[i], sizeof(path));
            if ((eos > path) && (eos - path < sizeof(path) - 1))
                *(eos++) = '/';
        }
        apr_cpystrn(eos, module, sizeof(path) - (eos - path));

        rv = apr_dso_load(&dlhandle, path, global);
        if (rv == APR_SUCCESS) { /* APR_EDSOOPEN */
            break;
        }
#if defined(APU_DSO_LIBDIR)
        else if (i < paths->nelts - 1) {
#else
        else {   /* No APU_DSO_LIBDIR to skip */
#endif
             /* try with apr-util-APU_MAJOR_VERSION appended */
            eos = apr_cpystrn(eos,
                              "apr-util-" APU_STRINGIFY(APU_MAJOR_VERSION) "/",
                              sizeof(path) - (eos - path));

            apr_cpystrn(eos, module, sizeof(path) - (eos - path));

            rv = apr_dso_load(&dlhandle, path, global);
            if (rv == APR_SUCCESS) { /* APR_EDSOOPEN */
                break;
            }
        }
    }

    if (rv != APR_SUCCESS) /* APR_ESYMNOTFOUND */
        return rv;

    rv = apr_dso_sym(dsoptr, dlhandle, modsym);
    if (rv != APR_SUCCESS) { /* APR_ESYMNOTFOUND */
        apr_dso_unload(dlhandle);
    }
    else {
        module = apr_pstrdup(global, module);
        apr_hash_set(dsos, module, APR_HASH_KEY_STRING, *dsoptr);
    }
    return rv;
}