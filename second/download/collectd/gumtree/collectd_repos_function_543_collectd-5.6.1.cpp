static void averaging_delete(averaging_t * avg)
{
    if (avg->ring_buffer != NULL)
    {
        free(avg->ring_buffer);
        avg->ring_buffer = NULL;
    }
    avg->ring_buffer_size = 0;
    avg->ring_buffer_sum  = 0L;
    avg->ring_buffer_head = 0;
}