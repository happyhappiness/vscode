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

static void update_child_status(h2_session *session, int status, const char *msg)
{
    /* Assume that we also change code/msg when something really happened and
     * avoid updating the scoreboard in between */
    if (session->last_status_code != status 
        || session->last_status_msg != msg) {
