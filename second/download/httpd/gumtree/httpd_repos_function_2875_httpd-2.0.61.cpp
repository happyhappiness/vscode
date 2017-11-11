void apr_proc_mutex_unix_setup_lock(void)
{
#if APR_HAS_POSIXSEM_SERIALIZE
    proc_mutex_posix_setup();
#endif
#if APR_HAS_SYSVSEM_SERIALIZE
    proc_mutex_sysv_setup();
#endif
#if APR_HAS_PROC_PTHREAD_SERIALIZE
    proc_mutex_proc_pthread_setup();
#endif
#if APR_HAS_FCNTL_SERIALIZE
    proc_mutex_fcntl_setup();
#endif
#if APR_HAS_FLOCK_SERIALIZE
    proc_mutex_flock_setup();
#endif
}