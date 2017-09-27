        parser->http_status = atoi(&line[sindex]);
        line[k] = keepchar;
        parser->state = H2_RP_HEADER_LINE;
        
        return APR_SUCCESS;
    }
    ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, task->c, APLOGNO(03467)
                  "h2_task(%s): unable to parse status line: %s", 
                  task->id, line);
    return APR_EINVAL;
}

apr_status_t h2_from_h1_parse_response(h2_task *task, ap_filter_t *f, 
