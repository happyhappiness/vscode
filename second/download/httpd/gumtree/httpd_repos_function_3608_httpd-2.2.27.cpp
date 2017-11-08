static apr_status_t proc_mutex_create(apr_proc_mutex_t *new_mutex, apr_lockmech_e mech, const char *fname)
{
    apr_status_t rv;

    if ((rv = proc_mutex_choose_method(new_mutex, mech)) != APR_SUCCESS) {
        return rv;
    }

    new_mutex->meth = new_mutex->inter_meth;

    if ((rv = new_mutex->meth->create(new_mutex, fname)) != APR_SUCCESS) {
        return rv;
    }

    return APR_SUCCESS;
}