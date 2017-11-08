static apr_status_t h2_to_h1_add_data_raw(h2_to_h1 *to_h1,
                                          const char *data, size_t len)
{
    apr_status_t status = APR_SUCCESS;

    if (to_h1->eos || !to_h1->eoh) {
        return APR_EINVAL;
    }
    
    status = apr_brigade_write(to_h1->bb, flush, to_h1, data, len);
    if (status == APR_SUCCESS) {
        status = h2_to_h1_flush(to_h1);
    }
    return status;
}