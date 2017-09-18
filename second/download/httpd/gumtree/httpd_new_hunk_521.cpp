        }
    }

    ap_update_child_status_from_indexes(0, thread_num, SERVER_DEAD, 
                                        (request_rec *) NULL);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf,
                 "Child %d: Worker thread %d exiting.", my_pid, thread_num);
}

static void cleanup_thread(thread *handles, int *thread_cnt, int thread_to_clean)
{
    int i;

