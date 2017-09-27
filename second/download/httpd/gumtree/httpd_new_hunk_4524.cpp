        parser->http_status = atoi(&line[sindex]);
        line[k] = keepchar;
        parser->state = H2_RP_HEADER_LINE;
        
        return APR_SUCCESS;
    }
    /* Seems like there is garbage on the connection. May be a leftover
     * from a previous proxy request. 
     * This should only happen if the H2_RESPONSE filter is not yet in 
     * place (post_read_request has not been reached and the handler wants
     * to write something. Probably just the interim response we are
     * waiting for. But if there is other data hanging around before
     * that, this needs to fail. */
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c, APLOGNO(03467)
                  "h2_task(%s): unable to parse status line: %s", 
                  task->id, line);
    return APR_EINVAL;
}

apr_status_t h2_from_h1_parse_response(h2_task *task, ap_filter_t *f, 
