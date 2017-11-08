static apr_status_t h2_sos_mplx_buffer(h2_sos *sos, apr_bucket_brigade *bb) 
{
    h2_sos_mplx *msos = sos->ctx;
    apr_status_t status = APR_SUCCESS;

    if (bb && !APR_BRIGADE_EMPTY(bb)) {
        H2_SOS_MPLX_OUT(APLOG_TRACE2, msos, "h2_sos_mplx set_response_pre");
        status = mplx_transfer(msos, sos->stream->id, sos->stream->pool);
        H2_SOS_MPLX_OUT(APLOG_TRACE2, msos, "h2_sos_mplx set_response_post");
    }
    return status;
}