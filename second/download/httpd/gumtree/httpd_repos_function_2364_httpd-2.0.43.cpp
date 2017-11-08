int apr_queue_size(apr_queue_t *queue) {
    return queue->nelts;
}