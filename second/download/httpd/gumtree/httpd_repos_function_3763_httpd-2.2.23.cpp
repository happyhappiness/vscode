static apr_status_t thread_once_cleanup(void *vcontrol)
{
    apr_thread_once_t *control = (apr_thread_once_t *)vcontrol;

    if (control->sem) {
        release_sem(control->sem);
        delete_sem(control->sem);
    }

    return APR_SUCCESS;
}