void apr_proc_mutex_unix_setup_lock(void)
{
    /* setup only needed for sysvsem and fnctl */
#if APR_HAS_SYSVSEM_SERIALIZE
    proc_mutex_sysv_setup();
#endif
#if APR_HAS_FCNTL_SERIALIZE
    proc_mutex_fcntl_setup();
#endif
}