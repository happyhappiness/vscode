static apr_status_t decrement_connection_count(void *cs_)
{
    event_conn_state_t *cs = cs_;
    switch (cs->pub.state) {
        case CONN_STATE_LINGER_NORMAL:
        case CONN_STATE_LINGER_SHORT:
            apr_atomic_dec32(&lingering_count);
            break;
        case CONN_STATE_SUSPENDED:
            apr_atomic_dec32(&suspended_count);
            break;
        default:
            break;
    }
    apr_atomic_dec32(&connection_count);
    return APR_SUCCESS;
}