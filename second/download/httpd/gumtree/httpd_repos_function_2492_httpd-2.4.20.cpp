static apr_status_t h2_sos_h2_status_readx(h2_sos *sos, h2_io_data_cb *cb, void *ctx,
                                           apr_off_t *plen, int *peos)
{
    return sos->prev->readx(sos->prev, cb, ctx, plen, peos);
}