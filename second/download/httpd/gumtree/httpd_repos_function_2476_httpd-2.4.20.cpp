static apr_status_t gset_encode_bit(gset_encoder *encoder, int bit)
{
    if (++encoder->bit >= 8) {
        if (++encoder->offset >= encoder->datalen) {
            apr_size_t nlen = encoder->datalen*2;
            unsigned char *ndata = apr_pcalloc(encoder->pool, nlen);
            if (!ndata) {
                return APR_ENOMEM;
            }
            memcpy(ndata, encoder->data, encoder->datalen);
            encoder->data = ndata;
            encoder->datalen = nlen;
        }
        encoder->bit = 0;
        encoder->data[encoder->offset] = 0xffu;
    }
    if (!bit) {
        encoder->data[encoder->offset] &= ~cbit_mask[encoder->bit];
    }
    return APR_SUCCESS;
}