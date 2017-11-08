apr_uint32_t ap_queue_info_get_idlers(fd_queue_info_t * queue_info)
{
    apr_int32_t val;
    val = (apr_int32_t)apr_atomic_read32((apr_uint32_t *)&queue_info->idlers);
    if (val < 0)
        return 0;
    return val;
}