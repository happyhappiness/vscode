static apr_status_t ptrans_pre_cleanup(void *dummy)
{
    event_conn_state_t *cs = dummy;

    if (cs->suspended) {
        notify_resume(cs);
    }
    return APR_SUCCESS;
}