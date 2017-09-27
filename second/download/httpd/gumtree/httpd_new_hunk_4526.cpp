                 */
                ap_remove_output_filter(f);
                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, f->c,
                              "h2_task(%s): eoc bucket passed", task->id);
                return ap_pass_brigade(f->next, bb);
            }
            else if (H2_BUCKET_IS_HEADERS(b)) {
                headers_passing = 1;
            }
            else if (!APR_BUCKET_IS_FLUSH(b)) { 
                body_bucket = b;
                break;
            }
        }
        
        if (eb) {
