static void shmcb_cyclic_ntoc_memcpy(unsigned int buf_size, unsigned char *data,
                                     unsigned int dest_offset, unsigned char *src,
                                     unsigned int src_len)
{
    if (dest_offset + src_len < buf_size)
        /* It be copied all in one go */
        memcpy(data + dest_offset, src, src_len);
    else {
        /* Copy the two splits */
        memcpy(data + dest_offset, src, buf_size - dest_offset);
        memcpy(data, src + buf_size - dest_offset,
               src_len + dest_offset - buf_size);
    }
}