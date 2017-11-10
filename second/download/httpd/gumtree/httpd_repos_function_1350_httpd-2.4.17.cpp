static void shmcb_cyclic_cton_memcpy(unsigned int buf_size, unsigned char *dest,
                                     const unsigned char *data, unsigned int src_offset,
                                     unsigned int src_len)
{
    if (src_offset + src_len < buf_size)
        /* It be copied all in one go */
        memcpy(dest, data + src_offset, src_len);
    else {
        /* Copy the two splits */
        memcpy(dest, data + src_offset, buf_size - src_offset);
        memcpy(dest + buf_size - src_offset, data,
               src_len + src_offset - buf_size);
    }
}