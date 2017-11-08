static void cleanup_streams(h2_session *session)
{
    stream_sel_ctx ctx;
    ctx.session = session;
    ctx.candidate = NULL;
    while (1) {
        h2_ihash_iter(session->streams, find_cleanup_stream, &ctx);
        if (ctx.candidate) {
            h2_session_stream_destroy(session, ctx.candidate);
            ctx.candidate = NULL;
        }
        else {
            break;
        }
    }
}