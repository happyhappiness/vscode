static int shmcb_cyclic_memcmp(unsigned int buf_size, unsigned char *data,
                               unsigned int dest_offset, 
                               const unsigned char *src,
                               unsigned int src_len)
{
    if (dest_offset + src_len < buf_size)
        /* It be compared all in one go */
        return memcmp(data + dest_offset, src, src_len);
    else {
        /* Compare the two splits */
        int diff;
        
        diff = memcmp(data + dest_offset, src, buf_size - dest_offset);
        if (diff) {
            return diff;
        }
        return memcmp(data, src + buf_size - dest_offset,
                      src_len + dest_offset - buf_size);
    }
}