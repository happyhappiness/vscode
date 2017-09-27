typedef struct {
    nghttp2_nv *nv;
    size_t nvlen;
    size_t offset;
} nvctx_t;

struct h2_stream *h2_session_push(h2_session *session, h2_stream *is,
                                  h2_push *push)
{
    apr_status_t status;
    h2_stream *stream;
    h2_ngheader *ngh;
