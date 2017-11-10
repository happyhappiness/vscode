static void shmcb_cyclic_ntoc_memcpy(
    unsigned int buf_size,
    unsigned char *data,
    unsigned int dest_offset,
    unsigned char *src, unsigned int src_len)
{
    /* Cover the case that src_len > buf_size */
    if (src_len > buf_size)
        src_len = buf_size;

    /* Can it be copied all in one go? */
    if (dest_offset + src_len < buf_size)
        /* yes */
        memcpy(data + dest_offset, src, src_len);
    else {
        /* no */
        memcpy(data + dest_offset, src, buf_size - dest_offset);
        memcpy(data, src + buf_size - dest_offset,
               src_len + dest_offset - buf_size);
    }
    return;
}