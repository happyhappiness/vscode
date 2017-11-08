static int make_worker(int slot)
{
    thread_id tid;

    if (slot + 1 > ap_max_child_assigned)
            ap_max_child_assigned = slot + 1;

    (void) ap_update_child_status_from_indexes(0, slot, SERVER_STARTING, (request_rec*)NULL);

    if (one_process) {
        set_signals();
        ap_scoreboard_image->parent[0].pid = getpid();
        ap_scoreboard_image->servers[0][slot].tid = find_thread(NULL);
        return 0;
    }

    tid = spawn_thread(worker_thread, "apache_worker", B_NORMAL_PRIORITY,
                       (void *)slot);
    if (tid < B_NO_ERROR) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, NULL,
            "spawn_thread: Unable to start a new thread");
        /* In case system resources are maxed out, we don't want
         * Apache running away with the CPU trying to fork over and
         * over and over again.
         */
        (void) ap_update_child_status_from_indexes(0, slot, SERVER_DEAD,
                                                   (request_rec*)NULL);

        sleep(10);
        return -1;
    }
    resume_thread(tid);

    ap_scoreboard_image->servers[0][slot].tid = tid;
    return 0;
}