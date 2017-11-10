apr_status_t apr_thread_join(apr_status_t *retval,
                                          apr_thread_t *thd)
{
    apr_status_t  stat;    
    NXThreadId_t dthr;

    if ((stat = NXThreadJoin(thd->td, &dthr, NULL)) == 0) {
        *retval = thd->exitval;
        return APR_SUCCESS;
    }
    else {
        return stat;
    }
}