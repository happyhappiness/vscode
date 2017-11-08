static int find_cleanup_stream(void *udata, void *sdata)
{
    stream_sel_ctx *ctx = udata;
    h2_stream *stream = sdata;
    if (H2_STREAM_CLIENT_INITIATED(stream->id)) {
        if (!ctx->session->local.accepting
            && stream->id > ctx->session->local.accepted_max) {
            ctx->candidate = stream;
            return 0;
        }
    }
    else {
        if (!ctx->session->remote.accepting
            && stream->id > ctx->session->remote.accepted_max) {
            ctx->candidate = stream;
            return 0;
        }
    }
    return 1;
}