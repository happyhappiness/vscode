apr_size_t h2_beam_get_files_beamed(h2_bucket_beam *beam)
{
    apr_size_t n = 0;
    h2_beam_lock bl;
    
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        n = beam->files_beamed;
        leave_yellow(beam, &bl);
    }
    return n;
}