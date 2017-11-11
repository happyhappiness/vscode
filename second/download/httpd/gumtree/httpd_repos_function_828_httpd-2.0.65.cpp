static unsigned int shmcb_cyclic_space(
    unsigned int buf_size,
    unsigned int start_offset,
    unsigned int next_offset)
{
    /* Is it the trivial case? */
    if (start_offset <= next_offset)
        return (next_offset - start_offset);              /* yes */
    else
        return ((buf_size - start_offset) + next_offset); /* no */
}