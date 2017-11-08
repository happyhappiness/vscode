static int h2_stream_id_cmp(const void *s1, const void *s2)
{
    h2_stream **pstream1 = (h2_stream **)s1;
    h2_stream **pstream2 = (h2_stream **)s2;
    return (*pstream1)->id - (*pstream2)->id;
}