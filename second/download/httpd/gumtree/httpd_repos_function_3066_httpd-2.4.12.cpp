static apr_lockmech_e proc_mutex_mech(apr_proc_mutex_t *pmutex)
{
    const char *mechname = apr_proc_mutex_name(pmutex);

    if (!strcmp(mechname, "sysvsem")) {
        return APR_LOCK_SYSVSEM;
    }
    else if (!strcmp(mechname, "flock")) {
        return APR_LOCK_FLOCK;
    }
    return APR_LOCK_DEFAULT;
}