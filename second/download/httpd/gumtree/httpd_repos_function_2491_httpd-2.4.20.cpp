static apr_status_t h2_sos_h2_status_prepare(h2_sos *sos, apr_off_t *plen, int *peos)
{
    return sos->prev->prepare(sos->prev, plen, peos);
}