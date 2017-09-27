#include "h2_ctx.h"
#include "h2_h2.h"
#include "h2_mplx.h"
#include "h2_ngn_shed.h"
#include "h2_request.h"
#include "h2_stream.h"
#include "h2_session.h"
#include "h2_task.h"
#include "h2_workers.h"
#include "h2_util.h"


/* utility for iterating over ihash stream sets */
typedef struct {
    h2_mplx *m;
    h2_stream *stream;
    apr_time_t now;
} stream_iter_ctx;

apr_status_t h2_mplx_child_init(apr_pool_t *pool, server_rec *s)
{
    return APR_SUCCESS;
}

#define H2_MPLX_ENTER(m)    \
    do { apr_status_t rv; if ((rv = apr_thread_mutex_lock(m->lock)) != APR_SUCCESS) {\
        return rv;\
    } } while(0)

#define H2_MPLX_LEAVE(m)    \
    apr_thread_mutex_unlock(m->lock)
 
#define H2_MPLX_ENTER_ALWAYS(m)    \
    apr_thread_mutex_lock(m->lock)

#define H2_MPLX_ENTER_MAYBE(m, lock)    \
    if (lock) apr_thread_mutex_lock(m->lock)

#define H2_MPLX_LEAVE_MAYBE(m, lock)    \
    if (lock) apr_thread_mutex_unlock(m->lock)

static void check_data_for(h2_mplx *m, h2_stream *stream, int lock);

static void stream_output_consumed(void *ctx, 
                                   h2_bucket_beam *beam, apr_off_t length)
{
    h2_stream *stream = ctx;
    h2_task *task = stream->task;
    
    if (length > 0 && task && task->assigned) {
        h2_req_engine_out_consumed(task->assigned, task->c, length); 
    }
}

static void stream_input_ev(void *ctx, h2_bucket_beam *beam)
{
    h2_stream *stream = ctx;
    h2_mplx *m = stream->session->mplx;
    apr_atomic_set32(&m->event_pending, 1); 
}

static void stream_input_consumed(void *ctx, h2_bucket_beam *beam, apr_off_t length)
{
    h2_stream_in_consumed(ctx, length);
}

static void stream_joined(h2_mplx *m, h2_stream *stream)
{
    ap_assert(!stream->task || stream->task->worker_done);
    
    h2_ihash_remove(m->shold, stream->id);
    h2_ihash_add(m->spurge, stream);
}

static void stream_cleanup(h2_mplx *m, h2_stream *stream)
{
    ap_assert(stream->state == H2_SS_CLEANUP);

    if (stream->input) {
        h2_beam_on_consumed(stream->input, NULL, NULL, NULL);
        h2_beam_abort(stream->input);
    }
    if (stream->output) {
        h2_beam_on_produced(stream->output, NULL, NULL);
        h2_beam_leave(stream->output);
    }
    
    h2_stream_cleanup(stream);

    h2_iq_remove(m->q, stream->id);
    h2_fifo_remove(m->readyq, stream);
    h2_ihash_remove(m->streams, stream->id);
    h2_ihash_add(m->shold, stream);
    
    if (!stream->task || stream->task->worker_done) {
        stream_joined(m, stream);
    }
    else if (stream->task) {
        stream->task->c->aborted = 1;
        apr_thread_cond_broadcast(m->task_thawed);
    }
}

/**
 * A h2_mplx needs to be thread-safe *and* if will be called by
 * the h2_session thread *and* the h2_worker threads. Therefore:
