
        if (!top->prev && top->main) {
            if (++subreqs >= slimit) {
                /* uuh, too much. */
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Request exceeded the limit of %d subrequest "
                              "nesting levels due to probable configuration "
                              "error. Use 'LimitInternalRecursion' to increase "
                              "the limit if necessary. Use 'LogLevel debug' to "
                              "get a backtrace.", slimit);

                /* post backtrace */
                log_backtrace(r);
