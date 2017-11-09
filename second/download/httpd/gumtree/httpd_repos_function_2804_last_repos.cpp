static void cleanup_unprocessed_streams(h2_session *session)
{
    h2_mplx_stream_do(session->mplx, rst_unprocessed_stream, session);
}