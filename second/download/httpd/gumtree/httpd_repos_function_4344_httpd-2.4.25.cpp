apr_status_t ap_queue_info_try_get_idler(fd_queue_info_t * queue_info)
{
    apr_int32_t new_idlers;
    new_idlers = apr_atomic_add32(&(queue_info->idlers), -1) - zero_pt;
    if (--new_idlers <= 0) {
        apr_atomic_inc32(&(queue_info->idlers));    /* back out dec */
        return APR_EAGAIN;
    }
    return APR_SUCCESS;
}