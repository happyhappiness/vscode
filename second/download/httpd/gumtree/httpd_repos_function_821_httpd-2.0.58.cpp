static void shmcb_cyclic_cton_memcpy(
    unsigned int buf_size,
    unsigned char *dest,
    unsigned char *data,
    unsigned int src_offset,
    unsigned int src_len)
{
    /* Cover the case that src_len > buf_size */
    if (src_len > buf_size)
        src_len = buf_size;

    /* Can it be copied all in one go? */
    if (src_offset + src_len < buf_size)
        /* yes */
        memcpy(dest, data + src_offset, src_len);
    else {
        /* no */
        memcpy(dest, data + src_offset, buf_size - src_offset);
        memcpy(dest + buf_size - src_offset, data,
               src_len + src_offset - buf_size);
    }
    return;
}