        }
        session->spare = pool;
    }
    return APR_SUCCESS;
}

int h2_session_push_enabled(h2_session *session)
{
    /* iff we can and they can and want */
    return (session->remote.accepting /* remote GOAWAY received */
            && h2_config_geti(session->config, H2_CONF_PUSH)
            && nghttp2_session_get_remote_settings(session->ngh2, 
                   NGHTTP2_SETTINGS_ENABLE_PUSH));
}

static apr_status_t h2_session_send(h2_session *session)
{
    apr_interval_time_t saved_timeout;
    int rv;
    apr_socket_t *socket;
    
    socket = ap_get_conn_socket(session->c);
    if (socket) {
        apr_socket_timeout_get(socket, &saved_timeout);
        apr_socket_timeout_set(socket, session->s->timeout);
    }
    
    rv = nghttp2_session_send(session->ngh2);
    
    if (socket) {
        apr_socket_timeout_set(socket, saved_timeout);
    }
    if (rv != 0) {
        if (nghttp2_is_fatal(rv)) {
            dispatch_event(session, H2_SESSION_EV_PROTO_ERROR, rv, nghttp2_strerror(rv));
            return APR_EGENERAL;
        }
    }
    
    session->unsent_promises = 0;
    session->unsent_submits = 0;
    
    return APR_SUCCESS;
}

static apr_status_t h2_session_receive(void *ctx, const char *data, 
                                       apr_size_t len, apr_size_t *readlen)
{
    h2_session *session = ctx;
    ssize_t n;
    
    if (len > 0) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                      "h2_session(%ld): feeding %ld bytes to nghttp2",
                      session->id, (long)len);
        n = nghttp2_session_mem_recv(session->ngh2, (const uint8_t *)data, len);
        if (n < 0) {
            if (nghttp2_is_fatal((int)n)) {
                dispatch_event(session, H2_SESSION_EV_PROTO_ERROR, (int)n, nghttp2_strerror(n));
                return APR_EGENERAL;
            }
        }
        else {
            *readlen = n;
            session->io.bytes_read += n;
        }
    }
    return APR_SUCCESS;
}

static apr_status_t h2_session_read(h2_session *session, int block)
{
    apr_status_t status, rstatus = APR_EAGAIN;
    conn_rec *c = session->c;
    apr_off_t read_start = session->io.bytes_read;
    
    while (1) {
        /* H2_IN filter handles all incoming data against the session.
         * We just pull at the filter chain to make it happen */
        status = ap_get_brigade(c->input_filters,
                                session->bbtmp, AP_MODE_READBYTES,
                                block? APR_BLOCK_READ : APR_NONBLOCK_READ,
                                APR_BUCKET_BUFF_SIZE);
        /* get rid of any possible data we do not expect to get */
        apr_brigade_cleanup(session->bbtmp); 

        switch (status) {
            case APR_SUCCESS:
                /* successful read, reset our idle timers */
                rstatus = APR_SUCCESS;
                if (block) {
                    /* successfull blocked read, try unblocked to
                     * get more. */
                    block = 0;
                }
                break;
            case APR_EAGAIN:
                return rstatus;
            case APR_TIMEUP:
                return status;
            default:
                if (session->io.bytes_read == read_start) {
                    /* first attempt failed */
                    if (APR_STATUS_IS_ETIMEDOUT(status)
                        || APR_STATUS_IS_ECONNABORTED(status)
                        || APR_STATUS_IS_ECONNRESET(status)
                        || APR_STATUS_IS_EOF(status)
                        || APR_STATUS_IS_EBADF(status)) {
                        /* common status for a client that has left */
                        ap_log_cerror( APLOG_MARK, APLOG_TRACE1, status, c,
                                      "h2_session(%ld): input gone", session->id);
                    }
                    else {
                        /* uncommon status, log on INFO so that we see this */
                        ap_log_cerror( APLOG_MARK, APLOG_DEBUG, status, c,
                                      APLOGNO(02950) 
                                      "h2_session(%ld): error reading, terminating",
                                      session->id);
                    }
                    return status;
                }
                /* subsequent failure after success(es), return initial
                 * status. */
                return rstatus;
        }
        if (!is_accepting_streams(session)) {
            break;
        }
        if ((session->io.bytes_read - read_start) > (64*1024)) {
            /* read enough in one go, give write a chance */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, c,
                          "h2_session(%ld): read 64k, returning", session->id);
            break;
        }
    }
    return rstatus;
}

static int unsubmitted_iter(void *ctx, void *val)
{
    h2_stream *stream = val;
    if (h2_stream_needs_submit(stream)) {
        *((int *)ctx) = 1;
        return 0;
    }
    return 1;
}

static int has_unsubmitted_streams(h2_session *session)
{
    int has_unsubmitted = 0;
    h2_ihash_iter(session->streams, unsubmitted_iter, &has_unsubmitted);
    return has_unsubmitted;
}

static int suspended_iter(void *ctx, void *val)
{
    h2_stream *stream = val;
    if (h2_stream_is_suspended(stream)) {
        *((int *)ctx) = 1;
        return 0;
    }
    return 1;
}

static int has_suspended_streams(h2_session *session)
{
    int has_suspended = 0;
    h2_ihash_iter(session->streams, suspended_iter, &has_suspended);
    return has_suspended;
}

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

static const char *StateNames[] = {
    "INIT",      /* H2_SESSION_ST_INIT */
    "DONE",      /* H2_SESSION_ST_DONE */
    "IDLE",      /* H2_SESSION_ST_IDLE */
    "BUSY",      /* H2_SESSION_ST_BUSY */
    "WAIT",      /* H2_SESSION_ST_WAIT */
    "LSHUTDOWN", /* H2_SESSION_ST_LOCAL_SHUTDOWN */
    "RSHUTDOWN", /* H2_SESSION_ST_REMOTE_SHUTDOWN */
};

static const char *state_name(h2_session_state state)
{
    if (state >= (sizeof(StateNames)/sizeof(StateNames[0]))) {
        return "unknown";
    }
    return StateNames[state];
}

static int is_accepting_streams(h2_session *session)
{
    switch (session->state) {
        case H2_SESSION_ST_IDLE:
        case H2_SESSION_ST_BUSY:
        case H2_SESSION_ST_WAIT:
            return 1;
        default:
            return 0;
    }
}

static void transit(h2_session *session, const char *action, h2_session_state nstate)
{
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03078)
                  "h2_session(%ld): transit [%s] -- %s --> [%s]", session->id,
                  state_name(session->state), action, state_name(nstate));
    session->state = nstate;
}

static void h2_session_ev_init(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_INIT:
            transit(session, "init", H2_SESSION_ST_BUSY);
            break;

        default:
            /* nop */
            break;
    }
}

static void h2_session_ev_local_goaway(h2_session *session, int arg, const char *msg)
{
    session->local.accepting = 0;
    cleanup_streams(session);
    switch (session->state) {
        case H2_SESSION_ST_LOCAL_SHUTDOWN:
            /* already did that? */
            break;
        case H2_SESSION_ST_IDLE:
        case H2_SESSION_ST_REMOTE_SHUTDOWN:
            /* all done */
            transit(session, "local goaway", H2_SESSION_ST_DONE);
            break;
        default:
            transit(session, "local goaway", H2_SESSION_ST_LOCAL_SHUTDOWN);
            break;
    }
}

static void h2_session_ev_remote_goaway(h2_session *session, int arg, const char *msg)
{
    session->remote.accepting = 0;
    cleanup_streams(session);
    switch (session->state) {
        case H2_SESSION_ST_REMOTE_SHUTDOWN:
            /* already received that? */
            break;
        case H2_SESSION_ST_IDLE:
        case H2_SESSION_ST_LOCAL_SHUTDOWN:
            /* all done */
            transit(session, "remote goaway", H2_SESSION_ST_DONE);
            break;
        default:
            transit(session, "remote goaway", H2_SESSION_ST_REMOTE_SHUTDOWN);
            break;
    }
}

static void h2_session_ev_conn_error(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_INIT:
        case H2_SESSION_ST_DONE:
        case H2_SESSION_ST_LOCAL_SHUTDOWN:
            /* just leave */
            transit(session, "conn error", H2_SESSION_ST_DONE);
            break;
        
        default:
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                          "h2_session(%ld): conn error -> shutdown", session->id);
            h2_session_shutdown(session, arg, msg, 0);
            break;
    }
}

static void h2_session_ev_proto_error(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_DONE:
        case H2_SESSION_ST_LOCAL_SHUTDOWN:
            /* just leave */
            transit(session, "proto error", H2_SESSION_ST_DONE);
            break;
        
        default:
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                          "h2_session(%ld): proto error -> shutdown", session->id);
            h2_session_shutdown(session, arg, msg, 0);
            break;
    }
}

static void h2_session_ev_conn_timeout(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_LOCAL_SHUTDOWN:
            transit(session, "conn timeout", H2_SESSION_ST_DONE);
            break;
        default:
            h2_session_shutdown(session, arg, msg, 1);
            transit(session, "conn timeout", H2_SESSION_ST_DONE);
            break;
    }
}

static void h2_session_ev_no_io(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_BUSY:
        case H2_SESSION_ST_LOCAL_SHUTDOWN:
        case H2_SESSION_ST_REMOTE_SHUTDOWN:
            /* nothing for input and output to do. If we remain
             * in this state, we go into a tight loop and suck up
             * CPU cycles. Ideally, we'd like to do a blocking read, but that
             * is not possible if we have scheduled tasks and wait
             * for them to produce something. */
            if (h2_conn_io_flush(&session->io) != APR_SUCCESS) {
                dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
            }
            if (h2_ihash_is_empty(session->streams)) {
                if (!is_accepting_streams(session)) {
                    /* We are no longer accepting new streams and have
                     * finished processing existing ones. Time to leave. */
                    h2_session_shutdown(session, arg, msg, 0);
                    transit(session, "no io", H2_SESSION_ST_DONE);
                }
                else {
                    apr_time_t now = apr_time_now();
                    /* When we have no streams, no task event are possible,
                     * switch to blocking reads */
                    transit(session, "no io", H2_SESSION_ST_IDLE);
                    session->idle_until = (session->remote.emitted_count? 
                                           session->s->keep_alive_timeout : 
                                           session->s->timeout) + now;
                    session->keep_sync_until = now + apr_time_from_sec(1);
                }
            }
            else if (!has_unsubmitted_streams(session)
                     && !has_suspended_streams(session)) {
                /* none of our streams is waiting for a response or
                 * new output data from task processing, 
                 * switch to blocking reads. We are probably waiting on
                 * window updates. */
                transit(session, "no io", H2_SESSION_ST_IDLE);
                session->idle_until = apr_time_now() + session->s->timeout;
                session->keep_sync_until = session->idle_until;
            }
            else {
                /* Unable to do blocking reads, as we wait on events from
                 * task processing in other threads. Do a busy wait with
                 * backoff timer. */
                transit(session, "no io", H2_SESSION_ST_WAIT);
            }
            break;
        default:
            /* nop */
            break;
    }
}

static void h2_session_ev_stream_ready(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_WAIT:
            transit(session, "stream ready", H2_SESSION_ST_BUSY);
            break;
        default:
            /* nop */
            break;
    }
}

static void h2_session_ev_data_read(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_IDLE:
        case H2_SESSION_ST_WAIT:
            transit(session, "data read", H2_SESSION_ST_BUSY);
            break;
            /* fall through */
        default:
            /* nop */
            break;
    }
}

static void h2_session_ev_ngh2_done(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_DONE:
            /* nop */
            break;
        default:
            transit(session, "nghttp2 done", H2_SESSION_ST_DONE);
            break;
    }
}

static void h2_session_ev_mpm_stopping(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_DONE:
        case H2_SESSION_ST_LOCAL_SHUTDOWN:
            /* nop */
            break;
        default:
            h2_session_shutdown(session, arg, msg, 0);
            break;
    }
}

static void h2_session_ev_pre_close(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_DONE:
        case H2_SESSION_ST_LOCAL_SHUTDOWN:
            /* nop */
            break;
        default:
            h2_session_shutdown(session, arg, msg, 1);
            break;
    }
}

static void dispatch_event(h2_session *session, h2_session_event_t ev, 
                      int arg, const char *msg)
{
    switch (ev) {
        case H2_SESSION_EV_INIT:
            h2_session_ev_init(session, arg, msg);
            break;            
        case H2_SESSION_EV_LOCAL_GOAWAY:
            h2_session_ev_local_goaway(session, arg, msg);
            break;
        case H2_SESSION_EV_REMOTE_GOAWAY:
            h2_session_ev_remote_goaway(session, arg, msg);
            break;
        case H2_SESSION_EV_CONN_ERROR:
            h2_session_ev_conn_error(session, arg, msg);
            break;
        case H2_SESSION_EV_PROTO_ERROR:
            h2_session_ev_proto_error(session, arg, msg);
            break;
        case H2_SESSION_EV_CONN_TIMEOUT:
            h2_session_ev_conn_timeout(session, arg, msg);
            break;
        case H2_SESSION_EV_NO_IO:
            h2_session_ev_no_io(session, arg, msg);
            break;
        case H2_SESSION_EV_STREAM_READY:
            h2_session_ev_stream_ready(session, arg, msg);
            break;
        case H2_SESSION_EV_DATA_READ:
            h2_session_ev_data_read(session, arg, msg);
            break;
        case H2_SESSION_EV_NGH2_DONE:
            h2_session_ev_ngh2_done(session, arg, msg);
            break;
        case H2_SESSION_EV_MPM_STOPPING:
            h2_session_ev_mpm_stopping(session, arg, msg);
            break;
        case H2_SESSION_EV_PRE_CLOSE:
            h2_session_ev_pre_close(session, arg, msg);
            break;
        default:
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                          "h2_session(%ld): unknown event %d", 
                          session->id, ev);
            break;
    }
    
    if (session->state == H2_SESSION_ST_DONE) {
        h2_mplx_abort(session->mplx);
    }
}

static const int MAX_WAIT_MICROS = 200 * 1000;

static void update_child_status(h2_session *session, int status, const char *msg)
{
    /* Assume that we also change code/msg when something really happened and
     * avoid updating the scoreboard in between */
    if (session->last_status_code != status 
        || session->last_status_msg != msg) {
        apr_snprintf(session->status, sizeof(session->status),
                     "%s, streams: %d/%d/%d/%d/%d (open/recv/resp/push/rst)", 
                     msg? msg : "-",
                     (int)h2_ihash_count(session->streams), 
                     (int)session->remote.emitted_count,
                     (int)session->responses_submitted,
                     (int)session->pushes_submitted,
                     (int)session->pushes_reset + session->streams_reset);
        ap_update_child_status_descr(session->c->sbh, status, session->status);
    }
}

apr_status_t h2_session_process(h2_session *session, int async)
{
    apr_status_t status = APR_SUCCESS;
    conn_rec *c = session->c;
    int rv, have_written, have_read, mpm_state, no_streams;

    ap_log_cerror( APLOG_MARK, APLOG_TRACE1, status, c,
                  "h2_session(%ld): process start, async=%d", session->id, async);
                  
    if (c->cs) {
        c->cs->state = CONN_STATE_WRITE_COMPLETION;
    }
    
    while (1) {
        have_read = have_written = 0;

        if (!ap_mpm_query(AP_MPMQ_MPM_STATE, &mpm_state)) {
            if (mpm_state == AP_MPMQ_STOPPING) {
                dispatch_event(session, H2_SESSION_EV_MPM_STOPPING, 0, NULL);
                break;
            }
        }
        
        session->status[0] = '\0';
        
        switch (session->state) {
            case H2_SESSION_ST_INIT:
                ap_update_child_status_from_conn(c->sbh, SERVER_BUSY_READ, c);
                if (!h2_is_acceptable_connection(c, 1)) {
                    update_child_status(session, SERVER_BUSY_READ, "inadequate security");
                    h2_session_shutdown(session, NGHTTP2_INADEQUATE_SECURITY, NULL, 1);
                } 
                else {
                    update_child_status(session, SERVER_BUSY_READ, "init");
                    status = h2_session_start(session, &rv);
                    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, c, APLOGNO(03079)
                                  "h2_session(%ld): started on %s:%d", session->id,
                                  session->s->server_hostname,
                                  c->local_addr->port);
                    if (status != APR_SUCCESS) {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
                    }
                    dispatch_event(session, H2_SESSION_EV_INIT, 0, NULL);
                }
                break;
                
            case H2_SESSION_ST_IDLE:
                no_streams = h2_ihash_is_empty(session->streams);
                update_child_status(session, (no_streams? SERVER_BUSY_KEEPALIVE
                                              : SERVER_BUSY_READ), "idle");
                /* make certain, the client receives everything before we idle */
                if (!session->keep_sync_until 
                    && async && no_streams && !session->r && session->remote.emitted_count) {
                    ap_log_cerror( APLOG_MARK, APLOG_TRACE1, status, c,
                                  "h2_session(%ld): async idle, nonblock read", session->id);
                    /* We do not return to the async mpm immediately, since under
                     * load, mpms show the tendency to throw keep_alive connections
                     * away very rapidly.
                     * So, if we are still processing streams, we wait for the
                     * normal timeout first and, on timeout, close.
                     * If we have no streams, we still wait a short amount of
                     * time here for the next frame to arrive, before handing
                     * it to keep_alive processing of the mpm.
                     */
                    status = h2_session_read(session, 0);
                    
                    if (status == APR_SUCCESS) {
                        have_read = 1;
                        dispatch_event(session, H2_SESSION_EV_DATA_READ, 0, NULL);
                    }
                    else if (APR_STATUS_IS_EAGAIN(status) || APR_STATUS_IS_TIMEUP(status)) {
                        if (apr_time_now() > session->idle_until) {
                            dispatch_event(session, H2_SESSION_EV_CONN_TIMEOUT, 0, NULL);
                        }
                        else {
                            status = APR_EAGAIN;
                            goto out;
                        }
                    }
                    else {
                        ap_log_cerror( APLOG_MARK, APLOG_DEBUG, status, c,
                                      "h2_session(%ld): idle, no data, error", 
                                      session->id);
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, "timeout");
                    }
                }
                else {
                    /* We wait in smaller increments, using a 1 second timeout.
                     * That gives us the chance to check for MPMQ_STOPPING often. 
                     */
                    status = h2_mplx_idle(session->mplx);
                    if (status != APR_SUCCESS) {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
                                       H2_ERR_ENHANCE_YOUR_CALM, "less is more");
                    }
                    h2_filter_cin_timeout_set(session->cin, apr_time_from_sec(1));
                    status = h2_session_read(session, 1);
                    if (status == APR_SUCCESS) {
                        have_read = 1;
                        dispatch_event(session, H2_SESSION_EV_DATA_READ, 0, NULL);
                    }
                    else if (status == APR_EAGAIN) {
                        /* nothing to read */
                    }
                    else if (APR_STATUS_IS_TIMEUP(status)) {
                        apr_time_t now = apr_time_now();
                        if (now > session->keep_sync_until) {
                            /* if we are on an async mpm, now is the time that
                             * we may dare to pass control to it. */
                            session->keep_sync_until = 0;
                        }
                        if (now > session->idle_until) {
                            dispatch_event(session, H2_SESSION_EV_CONN_TIMEOUT, 0, "timeout");
                        }
                        /* continue reading handling */
                    }
                    else {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, "error");
                    }
                }
                
                break;
                
            case H2_SESSION_ST_BUSY:
            case H2_SESSION_ST_LOCAL_SHUTDOWN:
            case H2_SESSION_ST_REMOTE_SHUTDOWN:
                if (nghttp2_session_want_read(session->ngh2)) {
                    ap_update_child_status(session->c->sbh, SERVER_BUSY_READ, NULL);
                    h2_filter_cin_timeout_set(session->cin, session->s->timeout);
                    status = h2_session_read(session, 0);
                    if (status == APR_SUCCESS) {
                        have_read = 1;
                        update_child_status(session, SERVER_BUSY_READ, "busy");
                        dispatch_event(session, H2_SESSION_EV_DATA_READ, 0, NULL);
                    }
                    else if (status == APR_EAGAIN) {
                        /* nothing to read */
                    }
                    else if (APR_STATUS_IS_TIMEUP(status)) {
                        dispatch_event(session, H2_SESSION_EV_CONN_TIMEOUT, 0, NULL);
                        break;
                    }
                    else {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
                    }
                }
                
                if (!h2_ihash_is_empty(session->streams)) {
                    /* resume any streams for which data is available again */
                    h2_session_resume_streams_with_data(session);
                    /* Submit any responses/push_promises that are ready */
                    status = h2_session_submit(session);
                    if (status == APR_SUCCESS) {
                        have_written = 1;
                    }
                    else if (status != APR_EAGAIN) {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
                                         H2_ERR_INTERNAL_ERROR, "submit error");
                        break;
                    }
                    /* send out window updates for our inputs */
                    status = h2_mplx_in_update_windows(session->mplx);
                    if (status != APR_SUCCESS && status != APR_EAGAIN) {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
                                         H2_ERR_INTERNAL_ERROR, "window update error");
                        break;
                    }
                }
                
                if (nghttp2_session_want_write(session->ngh2)) {
                    ap_update_child_status(session->c->sbh, SERVER_BUSY_WRITE, NULL);
                    status = h2_session_send(session);
                    if (status == APR_SUCCESS) {
                        have_written = 1;
                    }
                    else {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
                                         H2_ERR_INTERNAL_ERROR, "writing");
                        break;
                    }
                }
                
                if (have_read || have_written) {
                    if (session->wait_us) {
                        session->wait_us = 0;
                    }
                }
                else if (!nghttp2_session_want_write(session->ngh2)) {
                    dispatch_event(session, H2_SESSION_EV_NO_IO, 0, NULL);
                }
                break;
                
            case H2_SESSION_ST_WAIT:
                if (session->wait_us <= 0) {
                    session->wait_us = 10;
                    session->start_wait = apr_time_now();
                    if (h2_conn_io_flush(&session->io) != APR_SUCCESS) {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
                    }
                    update_child_status(session, SERVER_BUSY_READ, "wait");
                }
                else if ((apr_time_now() - session->start_wait) >= session->s->timeout) {
                    /* waited long enough */
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, APR_TIMEUP, c,
                                  "h2_session: wait for data");
                    dispatch_event(session, H2_SESSION_EV_CONN_TIMEOUT, 0, "timeout");
                    break;
                }
                else {
                    /* repeating, increase timer for graceful backoff */
                    session->wait_us = H2MIN(session->wait_us*2, MAX_WAIT_MICROS);
                }

                if (APLOGctrace1(c)) {
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                                  "h2_session: wait for data, %ld micros", 
                                  (long)session->wait_us);
                }
                status = h2_mplx_out_trywait(session->mplx, session->wait_us, 
                                             session->iowait);
                if (status == APR_SUCCESS) {
                    session->wait_us = 0;
                    dispatch_event(session, H2_SESSION_EV_DATA_READ, 0, NULL);
                }
                else if (status == APR_TIMEUP) {
                    /* go back to checking all inputs again */
                    transit(session, "wait cycle", session->local.accepting? 
                            H2_SESSION_ST_BUSY : H2_SESSION_ST_LOCAL_SHUTDOWN);
                }
                else {
                    ap_log_cerror(APLOG_MARK, APLOG_WARNING, status, c,
                                  "h2_session(%ld): waiting on conditional",
                                  session->id);
                    h2_session_shutdown(session, H2_ERR_INTERNAL_ERROR, 
                                        "cond wait error", 0);
                }
                break;
                
            case H2_SESSION_ST_DONE:
                update_child_status(session, SERVER_CLOSING, "done");
                status = APR_EOF;
                goto out;
                
            default:
                ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, c,
                              APLOGNO(03080)
                              "h2_session(%ld): unknown state %d", session->id, session->state);
                dispatch_event(session, H2_SESSION_EV_PROTO_ERROR, 0, NULL);
                break;
        }

        if (!nghttp2_session_want_read(session->ngh2) 
                 && !nghttp2_session_want_write(session->ngh2)) {
            dispatch_event(session, H2_SESSION_EV_NGH2_DONE, 0, NULL); 
        }
        if (session->reprioritize) {
            h2_mplx_reprioritize(session->mplx, stream_pri_cmp, session);
            session->reprioritize = 0;
        }
    }
    
out:
    ap_log_cerror( APLOG_MARK, APLOG_TRACE1, status, c,
                  "h2_session(%ld): [%s] process returns", 
                  session->id, state_name(session->state));

    if ((session->state != H2_SESSION_ST_DONE)
        && (APR_STATUS_IS_EOF(status)
            || APR_STATUS_IS_ECONNRESET(status) 
            || APR_STATUS_IS_ECONNABORTED(status))) {
            dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
        }

    status = (session->state == H2_SESSION_ST_DONE)? APR_EOF : APR_SUCCESS;
    if (session->state == H2_SESSION_ST_DONE) {
        if (!session->eoc_written) {
            session->eoc_written = 1;
            h2_conn_io_write_eoc(&session->io, session);
        }
    }
    
    return status;
}

apr_status_t h2_session_pre_close(h2_session *session, int async)
{
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c, 
                  "h2_session(%ld): pre_close", session->id);
    dispatch_event(session, H2_SESSION_EV_PRE_CLOSE, 0, "timeout");
    return APR_SUCCESS;
}
