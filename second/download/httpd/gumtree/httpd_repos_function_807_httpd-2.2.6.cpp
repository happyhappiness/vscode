static time_t shmcb_get_safe_time(time_t * ptr)
{
    time_t ret;
    shmcb_set_safe_time_ex((unsigned char *)(&ret),
                    (const unsigned char *)ptr);
    return ret;
}