                /* slot is still in use - back of the bus
                 */
                free_slots[free_length] = i;
            }
            ++free_length;
        }
        else if (child_threads_active == threads_per_child) {
            had_healthy_child = 1;
        }
        /* XXX if (!ps->quiescing)     is probably more reliable  GLA */
        if (!any_dying_threads) {
            last_non_dead = i;
            ++total_non_dead;
        }
    }

    if (retained->sick_child_detected) {
        if (had_healthy_child) {
            /* Assume this is a transient error, even though it may not be.  Leave
             * the server up in case it is able to serve some requests or the
             * problem will be resolved.
             */
            retained->sick_child_detected = 0;
        }
        else {
            /* looks like a basket case, as no child ever fully initialized; give up.
             */
            shutdown_pending = 1;
            child_fatal = 1;
            ap_log_error(APLOG_MARK, APLOG_ALERT, 0,
                         ap_server_conf, APLOGNO(02325)
                         "A resource shortage or other unrecoverable failure "
                         "was encountered before any child process initialized "
                         "successfully... httpd is exiting!");
            /* the child already logged the failure details */
            return;
        }
    }

    retained->max_daemons_limit = last_non_dead + 1;
