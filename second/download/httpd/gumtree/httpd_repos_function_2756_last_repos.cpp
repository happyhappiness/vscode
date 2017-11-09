static apr_size_t calc_space_left(h2_bucket_beam *beam)
{
    if (beam->max_buf_size > 0) {
        apr_off_t len = calc_buffered(beam);
        return (beam->max_buf_size > len? (beam->max_buf_size - len) : 0);
    }
    return APR_SIZE_MAX;
}