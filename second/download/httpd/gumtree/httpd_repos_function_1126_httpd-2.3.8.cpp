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