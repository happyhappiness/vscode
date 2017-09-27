                 * succeeds, get the context off the queue. It must be
                 * available, since there's only one consumer.
                 */
                rv = WaitForSingleObject(qwait_event, 1000);
                if (rv == WAIT_OBJECT_0)
                    continue;
                else {
                    if (rv == WAIT_TIMEOUT) {
                        /* somewhat-normal condition where threads are busy */
                        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00327)
                                     "mpm_get_completion_context: Failed to get a "
                                     "free context within 1 second");
                        *timeout = 1;
                    }
                    else {
                        /* should be the unexpected, generic WAIT_FAILED */
                        ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_os_error(),
                                     ap_server_conf, APLOGNO(00328)
                                     "mpm_get_completion_context: "
                                     "WaitForSingleObject failed to get free context");
                    }
                    return NULL;
                }
            } else {
                /* Allocate another context.
                 * Note: Multiple failures in the next two steps will cause
                 * the pchild pool to 'leak' storage. I don't think this
                 * is worth fixing...
                 */
