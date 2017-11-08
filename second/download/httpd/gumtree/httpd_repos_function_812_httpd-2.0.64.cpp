static void shmcb_set_safe_uint_ex(unsigned char *dest,
				const unsigned char *src)
{
    memcpy(dest, src, sizeof(unsigned int));
}