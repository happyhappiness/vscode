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
        if ((session->io.bytes_read - read_start) > (64*1024)) {
            /* read enough in one go, give write a chance */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, c,
                          "h2_session(%ld): read 64k, returning", session->id);
            break;
        }
    }
    return rstatus;
}

static const char *StateNames[] = {
    "INIT",      /* H2_SESSION_ST_INIT */
    "DONE",      /* H2_SESSION_ST_DONE */
    "IDLE",      /* H2_SESSION_ST_IDLE */
    "BUSY",      /* H2_SESSION_ST_BUSY */
    "WAIT",      /* H2_SESSION_ST_WAIT */
};

static const char *state_name(h2_session_state state)
{
    if (state >= (sizeof(StateNames)/sizeof(StateNames[0]))) {
        return "unknown";
    }
    return StateNames[state];
}
