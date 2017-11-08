int h2_stream_set_has_open_input(h2_stream_set *sp)
{
    int has_input_open = 0;
    h2_stream_set_iter(sp, input_open_iter, &has_input_open);
    return has_input_open;
}