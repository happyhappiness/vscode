static unsigned int shmcb_get_safe_uint(unsigned int *ptr)
{
    unsigned int ret;
    shmcb_set_safe_uint_ex((unsigned char *)(&ret),
                    (const unsigned char *)ptr);
    return ret;
}