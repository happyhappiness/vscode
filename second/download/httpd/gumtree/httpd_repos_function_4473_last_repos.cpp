apr_status_t ap_queue_interrupt_one(fd_queue_t * queue)
{
    return queue_interrupt(queue, 0);
}