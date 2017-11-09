apr_status_t h2_mplx_stream_cleanup(h2_mplx *m, h2_stream *stream)
{
    H2_MPLX_ENTER(m);
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c, 
                  H2_STRM_MSG(stream, "cleanup"));
    stream_cleanup(m, stream);        
    
    H2_MPLX_LEAVE(m);
    return APR_SUCCESS;
}