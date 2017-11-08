static apr_status_t proc_mutex_choose_method(apr_proc_mutex_t *new_mutex, apr_lockmech_e mech)
{
    switch (mech) {
    case APR_LOCK_FCNTL:
#if APR_HAS_FCNTL_SERIALIZE
        new_mutex->inter_meth = &mutex_fcntl_methods;
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_LOCK_FLOCK:
#if APR_HAS_FLOCK_SERIALIZE
        new_mutex->inter_meth = &mutex_flock_methods;
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_LOCK_SYSVSEM:
#if APR_HAS_SYSVSEM_SERIALIZE
        new_mutex->inter_meth = &mutex_sysv_methods;
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_LOCK_POSIXSEM:
#if APR_HAS_POSIXSEM_SERIALIZE
        new_mutex->inter_meth = &mutex_posixsem_methods;
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_LOCK_PROC_PTHREAD:
#if APR_HAS_PROC_PTHREAD_SERIALIZE
        new_mutex->inter_meth = &mutex_proc_pthread_methods;
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_LOCK_DEFAULT:
#if APR_USE_FLOCK_SERIALIZE
        new_mutex->inter_meth = &mutex_flock_methods;
#elif APR_USE_SYSVSEM_SERIALIZE
        new_mutex->inter_meth = &mutex_sysv_methods;
#elif APR_USE_FCNTL_SERIALIZE
        new_mutex->inter_meth = &mutex_fcntl_methods;
#elif APR_USE_PROC_PTHREAD_SERIALIZE
        new_mutex->inter_meth = &mutex_proc_pthread_methods;
#elif APR_USE_POSIXSEM_SERIALIZE
        new_mutex->inter_meth = &mutex_posixsem_methods;
#else
        return APR_ENOTIMPL;
#endif
        break;
    default:
        return APR_ENOTIMPL;
    }
    return APR_SUCCESS;
}