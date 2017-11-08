apr_off_t h2_beam_get_mem_used(h2_bucket_beam *beam)
{
    apr_bucket *b;
    apr_off_t l = 0;
    h2_beam_lock bl;
    
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        for (b = H2_BLIST_FIRST(&beam->send_list); 
            b != H2_BLIST_SENTINEL(&beam->send_list);
            b = APR_BUCKET_NEXT(b)) {
            if (APR_BUCKET_IS_FILE(b)) {
                /* do not count */
            }
            else {
                /* should all have determinate length */
                l += b->length;
            }
        }
        leave_yellow(beam, &bl);
    }
    return l;
}