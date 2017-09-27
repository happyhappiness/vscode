                                       apr_size_t *readlen);

static int is_accepting_streams(h2_session *session); 
static void dispatch_event(h2_session *session, h2_session_event_t ev, 
                             int err, const char *msg);

typedef struct stream_sel_ctx {
    h2_session *session;
    h2_stream *candidate;
} stream_sel_ctx;

static int find_cleanup_stream(void *udata, void *sdata)
