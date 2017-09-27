                for (i = 0; i < threads_per_child; i++)
                    ap_update_child_status_from_indexes(child_slot, i,
                                                        SERVER_DEAD, NULL);

                event_note_child_killed(child_slot, 0, 0);
                ps = &ap_scoreboard_image->parent[child_slot];
                ps->quiescing = 0;
                if (processed_status == APEXIT_CHILDSICK) {
                    /* resource shortage, minimize the fork rate */
                    retained->idle_spawn_rate[ps->bucket] = 1;
                }
                else if (remaining_children_to_start
                         && child_slot < ap_daemons_limit) {
                    /* we're still doing a 1-for-1 replacement of dead
                     * children with new children
                     */
                    make_child(ap_server_conf, child_slot, ps->bucket);
                    --remaining_children_to_start;
                }
            }
            else if (ap_unregister_extra_mpm_process(pid.pid, &old_gen) == 1) {

                event_note_child_killed(-1, /* already out of the scoreboard */
                                        pid.pid, old_gen);
                if (processed_status == APEXIT_CHILDSICK
                    && old_gen == retained->my_generation) {
                    /* resource shortage, minimize the fork rate */
                    for (i = 0; i < num_buckets; i++) {
                        retained->idle_spawn_rate[i] = 1;
                    }
                }
#if APR_HAS_OTHER_CHILD
            }
            else if (apr_proc_other_child_alert(&pid, APR_OC_REASON_DEATH,
                                                status) == 0) {
                /* handled */
#endif
            }
            else if (retained->is_graceful) {
                /* Great, we've probably just lost a slot in the
                 * scoreboard.  Somehow we don't know about this child.
                 */
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                             ap_server_conf, APLOGNO(00488)
