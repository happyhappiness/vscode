apr_status_t ap_queue_info_try_get_idler(fd_queue_info_t * queue_info)
{
    int prev_idlers;
    prev_idlers = apr_atomic_dec32((apr_uint32_t *)&(queue_info->idlers));
    if (prev_idlers <= 0) {
        apr_atomic_inc32((apr_uint32_t *)&(queue_info->idlers));    /* back out dec */
        return APR_EAGAIN;
    }
    return APR_SUCCESS;
}