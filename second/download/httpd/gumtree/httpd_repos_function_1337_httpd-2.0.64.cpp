static apr_status_t set_resource_limits(request_rec *r, 
                                        apr_procattr_t *procattr)
{
#if defined(RLIMIT_CPU)  || defined(RLIMIT_NPROC) || \
    defined(RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined (RLIMIT_AS)
    core_dir_config *conf = 
        (core_dir_config *)ap_get_module_config(r->per_dir_config,
                                                &core_module);
    apr_status_t rv;

#ifdef RLIMIT_CPU
    rv = apr_procattr_limit_set(procattr, APR_LIMIT_CPU, conf->limit_cpu);
    ap_assert(rv == APR_SUCCESS); /* otherwise, we're out of sync with APR */
#endif
#if defined(RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined(RLIMIT_AS)
    rv = apr_procattr_limit_set(procattr, APR_LIMIT_MEM, conf->limit_mem);
    ap_assert(rv == APR_SUCCESS); /* otherwise, we're out of sync with APR */
#endif
#ifdef RLIMIT_NPROC
    rv = apr_procattr_limit_set(procattr, APR_LIMIT_NPROC, conf->limit_nproc);
    ap_assert(rv == APR_SUCCESS); /* otherwise, we're out of sync with APR */
#endif

#endif /* if at least one limit defined */

    return APR_SUCCESS;
}