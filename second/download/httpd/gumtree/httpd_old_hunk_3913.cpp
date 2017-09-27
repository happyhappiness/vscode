                char buffer[1024];
                apr_size_t len = sizeof(buffer)-1;
                apr_brigade_flatten(bb, buffer, &len);
                buffer[len] = 0;
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                              "h2_task_input(%s): getline: %s",
                              input->env->id, buffer);
            }
            return status;
        }
        else {
            /* Hmm, well. There is mode AP_MODE_EATCRLF, but we chose not
             * to support it. Seems to work. */
