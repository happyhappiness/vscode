            apr_socket_timeout_set(cin->socket, saved_timeout);
        }
    }
    
    switch (status) {
        case APR_SUCCESS:
            status = recv_RAW_brigade(f->c, cin, cin->bb, block);
            break;
        case APR_EOF:
        case APR_EAGAIN:
        case APR_TIMEUP:
            if (trace1) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                              "h2_session(%ld): read", f->c->id);
            }
            break;
        default:
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, f->c, APLOGNO(03046)
                          "h2_session(%ld): error reading", f->c->id);
            break;
    }
    return status;
}

/*******************************************************************************
