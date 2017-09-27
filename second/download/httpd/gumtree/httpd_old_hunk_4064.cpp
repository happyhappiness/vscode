                apr_brigade_flatten(bb, buffer, &len);
                buffer[len] = 0;
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                              "h2_task_input(%s): getline: %s",
                              input->task->id, buffer);
            }
            return status;
        }
        else {
            /* Hmm, well. There is mode AP_MODE_EATCRLF, but we chose not
             * to support it. Seems to work. */
            ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOTIMPL, f->c,
                          APLOGNO(02942) 
                          "h2_task_input, unsupported READ mode %d", mode);
            return APR_ENOTIMPL;
        }
    }
    
    if (is_aborted(f)) {
        return APR_ECONNABORTED;
    }
    
    return (block == APR_NONBLOCK_READ)? APR_EAGAIN : APR_EOF;
}

