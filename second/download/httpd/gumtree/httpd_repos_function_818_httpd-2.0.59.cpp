static unsigned int shmcb_cyclic_increment(
    unsigned int buf_size,
    unsigned int start_pos,
    unsigned int to_add)
{
    start_pos += to_add;
    while (start_pos >= buf_size)
        start_pos -= buf_size;
    return start_pos;
}