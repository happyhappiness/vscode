static apr_status_t h2_session_submit(h2_session *session)
{
    apr_status_t status = APR_EAGAIN;
    h2_stream *stream;
    
    if (has_unsubmitted_streams(session)) {
        /* If we have responses ready, submit them now. */
        while ((stream = h2_mplx_next_submit(session->mplx, session->streams))) {
            status = submit_response(session, stream);
            ++session->unsent_submits;
            
            /* Unsent push promises are written immediately, as nghttp2
             * 1.5.0 realizes internal stream data structures only on 
             * send and we might need them for other submits. 
             * Also, to conserve memory, we send at least every 10 submits
             * so that nghttp2 does not buffer all outbound items too 
             * long.
             */
            if (status == APR_SUCCESS 
                && (session->unsent_promises || session->unsent_submits > 10)) {
                status = h2_session_send(session);
                if (status != APR_SUCCESS) {
                    break;
                }
            }
        }
    }
    return status;
}