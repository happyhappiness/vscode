                /* slot is still in use - back of the bus
                 */
                free_slots[free_length] = i;
            }
            ++free_length;
        }
        /* XXX if (!ps->quiescing)     is probably more reliable  GLA */
        if (!any_dying_threads) {
            last_non_dead = i;
            ++total_non_dead;
        }
    }

    if (retained->sick_child_detected) {
        if (active_thread_count > 0) {
            /* some child processes appear to be working.  don't kill the
             * whole server.
             */
            retained->sick_child_detected = 0;
        }
        else {
            /* looks like a basket case.  give up.
             */
            shutdown_pending = 1;
            child_fatal = 1;
            ap_log_error(APLOG_MARK, APLOG_ALERT, 0,
                         ap_server_conf, APLOGNO(00483)
                         "No active workers found..."
                         " Apache is exiting!");
            /* the child already logged the failure details */
            return;
        }
    }

    retained->max_daemons_limit = last_non_dead + 1;
