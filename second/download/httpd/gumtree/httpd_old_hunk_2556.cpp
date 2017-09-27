/*
 * High-Level "handlers" as per ssl_scache.c
 * subcache internals are deferred to shmcb_subcache_*** functions lower down
 */

static const char *socache_shmcb_create(ap_socache_instance_t **context,
                                        const char *arg, 
                                        apr_pool_t *tmp, apr_pool_t *p)
{
    ap_socache_instance_t *ctx;
    char *path, *cp, *cp2;

    /* Allocate the context. */
    *context = ctx = apr_pcalloc(p, sizeof *ctx);
    
    ctx->shm_size  = 1024*512; /* 512KB */

    if (!arg || *arg == '\0') {
        /* Use defaults. */
        return NULL;
    }
    
    ctx->data_file = path = ap_server_root_relative(p, arg);

    cp = strrchr(path, '(');
    cp2 = path + strlen(path) - 1;
    if (cp) {
        char *endptr;
        if (*cp2 != ')') {
            return "Invalid argument: no closing parenthesis or cache size "
                   "missing after pathname with parenthesis";
        }
        *cp++ = '\0';
        *cp2  = '\0';
        
        
        ctx->shm_size = strtol(cp, &endptr, 10);
        if (endptr != cp2) {
            return "Invalid argument: cache size not numerical";
        }
        
        if (ctx->shm_size < 8192) {
            return "Invalid argument: size has to be >= 8192 bytes";
            
        }
        
        if (ctx->shm_size >= SHMCB_MAX_SIZE) {
            return apr_psprintf(tmp,
                                "Invalid argument: size has "
                                "to be < %d bytes on this platform", 
                                SHMCB_MAX_SIZE);
            
        }
    }
    else if (cp2 >= path && *cp2 == ')') {
        return "Invalid argument: no opening parenthesis";
    }

    return NULL;
}

static apr_status_t socache_shmcb_init(ap_socache_instance_t *ctx,
                                       const char *namespace, 
                                       const struct ap_socache_hints *hints,
                                       server_rec *s, apr_pool_t *p)
{
    void *shm_segment;
    apr_size_t shm_segsize;
    apr_status_t rv;
    SHMCBHeader *header;
    unsigned int num_subcache, num_idx, loop;
    apr_size_t avg_obj_size, avg_id_len;

    /* Create shared memory segment */
    if (ctx->data_file == NULL) {
        const char *path = apr_pstrcat(p, DEFAULT_SHMCB_PREFIX, namespace, 
                                       DEFAULT_SHMCB_SUFFIX, NULL);

        ctx->data_file = ap_server_root_relative(p, path);
    }

    /* Use anonymous shm by default, fall back on name-based. */
    rv = apr_shm_create(&ctx->shm, ctx->shm_size, NULL, p);
    if (APR_STATUS_IS_ENOTIMPL(rv)) {
        /* If anon shm isn't supported, fail if no named file was
         * configured successfully; the ap_server_root_relative call
         * above will return NULL for invalid paths. */
        if (ctx->data_file == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                         "Could not use default path '%s' for shmcb socache",
                         ctx->data_file);
            return APR_EINVAL;
        }

        /* For a name-based segment, remove it first in case of a
