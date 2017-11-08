static const char *get_mutex_filename(apr_pool_t *p, mutex_cfg_t *mxcfg,
                                      const char *type,
                                      const char *instance_id)
{
    const char *pid_suffix = "";

    if (!mutex_needs_file(mxcfg->mech)) {
        return NULL;
    }

#if HAVE_UNISTD_H
    if (!mxcfg->omit_pid) {
        pid_suffix = apr_psprintf(p, ".%" APR_PID_T_FMT, getpid());
    }
#endif

    return ap_server_root_relative(p,
                                   apr_pstrcat(p,
                                               mxcfg->dir,
                                               "/",
                                               type,
                                               instance_id ? "-" : "",
                                               instance_id ? instance_id : "",
                                               pid_suffix,
                                               NULL));
}