#include "h2_task.h"
#include "h2_ctx.h"
#include "h2_task.h"
#include "h2_util.h"


static int state_transition[][7] = {
    /*  ID OP RL RR CI CO CL */
/*ID*/{  1, 0, 0, 0, 0, 0, 0 },
/*OP*/{  1, 1, 0, 0, 0, 0, 0 },
/*RL*/{  0, 0, 1, 0, 0, 0, 0 },
/*RR*/{  0, 0, 0, 1, 0, 0, 0 },
/*CI*/{  1, 1, 0, 0, 1, 0, 0 },
/*CO*/{  1, 1, 0, 0, 0, 1, 0 },
/*CL*/{  1, 1, 0, 0, 1, 1, 1 },
};

static void H2_STREAM_OUT_LOG(int lvl, h2_stream *s, const char *tag)
{
    if (APLOG_C_IS_LEVEL(s->session->c, lvl)) {
        conn_rec *c = s->session->c;
        char buffer[4 * 1024];
        const char *line = "(null)";
        apr_size_t len, bmax = sizeof(buffer)/sizeof(buffer[0]);
        
        len = h2_util_bb_print(buffer, bmax, tag, "", s->out_buffer);
        ap_log_cerror(APLOG_MARK, lvl, 0, c, "bb_dump(%s): %s", 
                      c->log_id, len? buffer : line);
    }
}

static int set_state(h2_stream *stream, h2_stream_state_t state)
{
    int allowed = state_transition[state][stream->state];
    if (allowed) {
        stream->state = state;
        return 1;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, stream->session->c, APLOGNO(03081)
                  "h2_stream(%ld-%d): invalid state transition from %d to %d", 
                  stream->session->id, stream->id, stream->state, state);
    return 0;
}

static int close_input(h2_stream *stream) 
{
    switch (stream->state) {
        case H2_STREAM_ST_CLOSED_INPUT:
        case H2_STREAM_ST_CLOSED:
            return 0; /* ignore, idempotent */
        case H2_STREAM_ST_CLOSED_OUTPUT:
            /* both closed now */
            set_state(stream, H2_STREAM_ST_CLOSED);
            break;
        default:
            /* everything else we jump to here */
            set_state(stream, H2_STREAM_ST_CLOSED_INPUT);
            break;
    }
    return 1;
}

static int input_closed(h2_stream *stream) 
{
    switch (stream->state) {
        case H2_STREAM_ST_OPEN:
        case H2_STREAM_ST_CLOSED_OUTPUT:
            return 0;
        default:
            return 1;
    }
}

static int close_output(h2_stream *stream) 
{
    switch (stream->state) {
        case H2_STREAM_ST_CLOSED_OUTPUT:
        case H2_STREAM_ST_CLOSED:
            return 0; /* ignore, idempotent */
        case H2_STREAM_ST_CLOSED_INPUT:
            /* both closed now */
            set_state(stream, H2_STREAM_ST_CLOSED);
            break;
        default:
            /* everything else we jump to here */
            set_state(stream, H2_STREAM_ST_CLOSED_OUTPUT);
            break;
    }
    return 1;
}

static int input_open(const h2_stream *stream) 
{
    switch (stream->state) {
        case H2_STREAM_ST_OPEN:
        case H2_STREAM_ST_CLOSED_OUTPUT:
            return 1;
        default:
            return 0;
    }
}

static int output_open(h2_stream *stream) 
{
    switch (stream->state) {
        case H2_STREAM_ST_OPEN:
        case H2_STREAM_ST_CLOSED_INPUT:
            return 1;
        default:
            return 0;
    }
}

static void prep_output(h2_stream *stream) {
    conn_rec *c = stream->session->c;
    if (!stream->out_buffer) {
        stream->out_buffer = apr_brigade_create(stream->pool, c->bucket_alloc);
    }
}

static void prepend_response(h2_stream *stream, h2_headers *response)
{
    conn_rec *c = stream->session->c;
    apr_bucket *b;
    
    prep_output(stream);
    b = h2_bucket_headers_create(c->bucket_alloc, response);
    APR_BRIGADE_INSERT_HEAD(stream->out_buffer, b);
}

static apr_status_t stream_pool_cleanup(void *ctx)
{
    h2_stream *stream = ctx;
    apr_status_t status;
    
    ap_assert(stream->can_be_cleaned);
    if (stream->files) {
        apr_file_t *file;
        int i;
        for (i = 0; i < stream->files->nelts; ++i) {
            file = APR_ARRAY_IDX(stream->files, i, apr_file_t*);
            status = apr_file_close(file);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, stream->session->c, 
                          "h2_stream(%ld-%d): destroy, closed file %d", 
                          stream->session->id, stream->id, i);
        }
        stream->files = NULL;
    }
    return APR_SUCCESS;
}

h2_stream *h2_stream_open(int id, apr_pool_t *pool, h2_session *session,
                          int initiated_on)
{
    h2_stream *stream = apr_pcalloc(pool, sizeof(h2_stream));
    
    stream->id           = id;
    stream->initiated_on = initiated_on;
    stream->created      = apr_time_now();
    stream->state        = H2_STREAM_ST_IDLE;
    stream->pool         = pool;
    stream->session      = session;
    stream->can_be_cleaned = 1;
    
    h2_beam_create(&stream->input, pool, id, "input", H2_BEAM_OWNER_SEND, 0);
    h2_beam_create(&stream->output, pool, id, "output", H2_BEAM_OWNER_RECV, 0);
    
    set_state(stream, H2_STREAM_ST_OPEN);
    apr_pool_cleanup_register(pool, stream, stream_pool_cleanup, 
                              apr_pool_cleanup_null);
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03082)
                  "h2_stream(%ld-%d): opened", session->id, stream->id);
    return stream;
}

void h2_stream_cleanup(h2_stream *stream)
{
    apr_status_t status;
