static apr_status_t h2_sos_h2_status_read_to(h2_sos *sos, apr_bucket_brigade *bb, 
                                             apr_off_t *plen, int *peos)
{
    return sos->prev->read_to(sos->prev, bb, plen, peos);
}