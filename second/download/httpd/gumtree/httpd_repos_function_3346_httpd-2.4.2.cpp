static apr_status_t decrement_connection_count(void *dummy) {
    apr_atomic_dec32(&connection_count);
    return APR_SUCCESS;
}