apr_status_t h2_to_h1_close(h2_to_h1 *to_h1)
{
    apr_status_t status = APR_SUCCESS;
    if (!to_h1->eos) {
        if (to_h1->chunked) {
            status = h2_to_h1_add_data_raw(to_h1, "0\r\n\r\n", 5);
        }
        to_h1->eos = 1;
        status = h2_to_h1_flush(to_h1);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, to_h1->m->c,
                      "h2_to_h1(%d): close", to_h1->stream_id);
        
        status = h2_mplx_in_close(to_h1->m, to_h1->stream_id);
    }
    return status;
}