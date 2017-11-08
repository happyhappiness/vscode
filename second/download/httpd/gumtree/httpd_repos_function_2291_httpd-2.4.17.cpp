static int h2_stream_id_cmp(const void *s1, const void *s2)
{
    h2_io **pio1 = (h2_io **)s1;
    h2_io **pio2 = (h2_io **)s2;
    return (*pio1)->id - (*pio2)->id;
}