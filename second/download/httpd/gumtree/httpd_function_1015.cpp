static int make_worker(int slot)
{
    thread_id tid;
    proc_info *my_info = (proc_info *)malloc(sizeof(proc_info)); /* freed by thread... */

    if (my_info == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, errno, ap_server_conf,
            "malloc: out of memory");
        clean_child_exit(APEXIT_CHILDFATAL);
    }
    
    my_info->slot = slot;
    apr_pool_create(&my_info->tpool, pchild);
    
    if (slot + 1 > ap_max_child_assigned)
	    ap_max_child_assigned = slot + 1;

    if (one_process) {
    	set_signals();
        ap_scoreboard_image->parent[0].pid = getpid();
        return 0;
    }

    (void) ap_update_child_status_from_indexes(0, slot, SERVER_STARTING, (request_rec*)NULL);
    tid = spawn_thread(worker_thread, "apache_worker", B_NORMAL_PRIORITY,
        my_info);
    if (tid < B_NO_ERROR) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, NULL, 
            "spawn_thread: Unable to start a new thread");
        /* In case system resources are maxxed out, we don't want
         * Apache running away with the CPU trying to fork over and
         * over and over again. 
         */
        (void) ap_update_child_status_from_indexes(0, slot, SERVER_DEAD, 
                                                   (request_rec*)NULL);
        
    	sleep(10);
        free(my_info);
        
    	return -1;
    }
    resume_thread(tid);

    ap_scoreboard_image->servers[0][slot].tid = tid;
    return 0;
}