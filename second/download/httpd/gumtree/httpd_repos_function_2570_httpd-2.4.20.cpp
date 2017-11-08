static int h2_session_resume_streams_with_data(h2_session *session)
{
    AP_DEBUG_ASSERT(session);
    if (!h2_ihash_is_empty(session->streams)
        && session->mplx && !session->mplx->aborted) {
        resume_ctx ctx;
        
        ctx.session      = session;
        ctx.resume_count = 0;

        /* Resume all streams where we have data in the out queue and
         * which had been suspended before. */
        h2_ihash_iter(session->streams, resume_on_data, &ctx);
        return ctx.resume_count;
    }
    return 0;
}