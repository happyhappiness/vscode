                    child_slot = i;
                    break;
                }
            }
            if (child_slot >= 0) {
                ap_scoreboard_image->servers[0][child_slot].tid = 0;
                (void) ap_update_child_status_from_indexes(0, child_slot,
                                                           SERVER_DEAD,
                                                           (request_rec*)NULL);

                if (remaining_threads_to_start
		            && child_slot < ap_thread_limit) {
                    /* we're still doing a 1-for-1 replacement of dead
                     * children with new children
                     */
                    make_worker(child_slot);
                    --remaining_threads_to_start;
		        }
/* TODO
#if APR_HAS_OTHER_CHILD
            }
            else if (apr_proc_other_child_refresh(&pid, status) == 0) {
#endif
*/
            }
            else if (is_graceful) {
                /* Great, we've probably just lost a slot in the
                 * scoreboard.  Somehow we don't know about this
                 * child.
                 */
                 ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf,
			                  "long lost child came home! (pid %ld)", pid.pid);
            }

            /* Don't perform idle maintenance when a child dies,
             * only do it when there's a timeout.  Remember only a
             * finite number of children can die, and it's pretty
             * pathological for a lot to die suddenly.
             */
             continue;
